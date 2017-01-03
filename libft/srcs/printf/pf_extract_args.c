/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_extract_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:19:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 03:56:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_parse.h"

static int	create_arg(t_list **args, size_t n, t_pf_conv *conv, int type)
{
	t_pf_arg	arg;
	t_list		*el;

	arg.conv = conv;
	arg.type = type;
	if (n > 0)
		arg.n = n;
	else if (*args)
		arg.n = ((t_pf_arg *)((*args)->content))->n + 1;
	else
		arg.n = 1;
	if (!(el = ft_lstnew((void *)&arg, sizeof(arg))))
		return (0);
	ft_lstadd(args, el);
	return (1);
}

static void	*create_conv_args(t_list *el, void *acc)
{
	t_list		**args;
	t_pf_conv	*conv;

	args = (t_list **)acc;
	conv = (t_pf_conv *)(el->content);
	if (conv->format)
	{
		if ((conv->info->width_arg >= 0
					&& !(create_arg(args, conv->info->width_arg, conv, -1)))
				|| (conv->info->prec_arg >= 0
					&& !(create_arg(args, conv->info->prec_arg, conv, 1)))
				|| !(create_arg(args, conv->info->arg, conv, 0)))
			return (NULL);
	}
	return (args);
}

static int	arg_order(t_list *e1, t_list *e2)
{
	t_pf_arg	*arg1;
	t_pf_arg	*arg2;

	arg1 = (t_pf_arg *)(e1->content);
	arg2 = (t_pf_arg *)(e2->content);
	return (arg1->n > arg2->n);
}

static int	do_extract_args(t_list *args, va_list ap)
{
	t_pf_arg	*arg;
	t_pf_arg	*next;
	va_list		cp;
	int			same_arg;

	if (!args)
		return (1);
	arg = (t_pf_arg *)args->content;
	next = args->next ? (t_pf_arg *)(args->next->content) : NULL;
	if (next && next->n > arg->n + 1)
		return (0);
	if ((same_arg = next && next->n == arg->n))
		va_copy(cp, ap);
	if (arg->type < 0)
		arg->conv->info->width = va_arg(same_arg ? cp : ap, int);
	else if (arg->type > 0)
		arg->conv->info->prec = va_arg(same_arg ? cp : ap, int);
	else
		arg->conv->arg = arg->conv->format->get_arg(arg->conv->info,
													same_arg ? cp : ap);
	if (same_arg)
		va_end(cp);
	if (arg->type == 0 && !(arg->conv->arg))
		return (0);
	return (do_extract_args(args->next, ap));
}

int			pf_extract_args(t_list *convs, va_list ap)
{
	t_list			*args;
	int				res;

	args = NULL;
	res = 0;
	if (ft_lstfoldl(convs, &args, &create_conv_args))
	{
		ft_lstsort(&args, &arg_order);
		if (do_extract_args(args, ap))
			res = 1;
	}
	ft_lstdel(&args, &ft_lstdelcnt);
	return (res);
}
