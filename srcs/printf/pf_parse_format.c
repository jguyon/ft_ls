/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:45:07 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 00:20:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static t_list	*create_conv(char **next, const char *prev)
{
	t_pf_conv	conv;
	t_list		*el;

	conv.prev = prev;
	conv.len = *next - prev;
	conv.info = NULL;
	conv.format = NULL;
	conv.arg = NULL;
	el = NULL;
	if (!(**next) || ((conv.info = pf_get_info(next))
						&& (conv.format = pf_get_format(conv.info))))
		el = ft_lstnew(&conv, sizeof(conv));
	if (!(el))
		ft_memdel((void **)&(conv.info));
	return (el);
}

static int		check_args(t_list *prev, t_list *next)
{
	t_pf_conv	*prev_conv;
	t_pf_conv	*next_conv;

	prev_conv = prev ? (t_pf_conv *)prev->content : NULL;
	next_conv = next ? (t_pf_conv *)next->content : NULL;
	if (next_conv && next_conv->info && next_conv->info->spec != PF_SPEC_FMT)
	{
		if (next_conv->info->arg > 0 && (next_conv->info->width_arg == 0
										|| next_conv->info->prec_arg == 0))
			return (0);
		if (next_conv->info->arg == 0 && (next_conv->info->width_arg > 0
											|| next_conv->info->prec_arg > 0))
			return (0);
		if (prev_conv && prev_conv->info
				&& prev_conv->info->spec != PF_SPEC_FMT)
		{
			if (prev_conv->info->arg == 0 && next_conv->info->arg > 0)
				return (0);
			if (prev_conv->info->arg > 0 && next_conv->info->arg == 0)
				return (0);
		}
	}
	return (1);
}

t_list			*pf_parse_format(const char *format)
{
	t_list	*convs;
	char	*next;
	t_list	*el;
	t_list	*prev;
	t_list	**next_el;

	convs = NULL;
	next_el = &convs;
	prev = NULL;
	while ((next = ft_strchrnul(format, (int)PF_FORMAT_START)))
	{
		if (!(el = create_conv(&next, format)) || !(check_args(prev, el)))
		{
			pf_del_convs(&el);
			pf_del_convs(&convs);
			return (NULL);
		}
		prev = el;
		*next_el = el;
		next_el = &(el->next);
		format = next;
		if (!(*format))
			break ;
	}
	return (convs);
}
