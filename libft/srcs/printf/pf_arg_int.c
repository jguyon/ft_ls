/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:09:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 04:01:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_strings.h"
#include "priv/pf_convert.h"

static intmax_t	cast_arg(t_pf_int *arg, t_pf_info *info, va_list ap)
{
	intmax_t	n;

	if (info->spec == PF_SPEC_LNG || info->mod == PF_MOD_L)
		n = va_arg(ap, long);
	else if (info->mod == PF_MOD_HH)
		n = (signed char)va_arg(ap, int);
	else if (info->mod == PF_MOD_H)
		n = (short)va_arg(ap, int);
	else if (info->mod == PF_MOD_LL)
		n = va_arg(ap, long long);
	else if (info->mod == PF_MOD_J)
		n = va_arg(ap, intmax_t);
	else if (info->mod == PF_MOD_Z)
		n = va_arg(ap, ssize_t);
	else
		n = va_arg(ap, int);
	arg->n = (uintmax_t)(n < 0 ? -n : n);
	return (n);
}

static void		set_sign(t_pf_int *arg, t_pf_info *info, intmax_t n)
{
	if (n < 0)
		ft_strcpy(arg->prefix, "-");
	else if (PF_HAS_FLAG(info->flags, PF_FLAG_PLS))
		ft_strcpy(arg->prefix, "+");
	else if (PF_HAS_FLAG(info->flags, PF_FLAG_SPC))
		ft_strcpy(arg->prefix, " ");
}

void			*pf_arg_int(t_pf_info *info, va_list ap)
{
	t_pf_int	*arg;
	intmax_t	n;

	if (!(arg = (t_pf_int *)ft_memalloc(sizeof(*arg))))
		return (NULL);
	n = cast_arg(arg, info, ap);
	set_sign(arg, info, n);
	arg->base = 10;
	arg->upper_base = 0;
	return ((void *)arg);
}
