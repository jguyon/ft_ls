/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_uint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:15:09 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 12:33:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

void	cast_arg(t_pf_int *arg, t_pf_info *info, va_list ap)
{
	if (info->spec == PF_SPEC_ADDR)
		arg->n = (uintmax_t)va_arg(ap, void *);
	else if (info->spec == PF_SPEC_ULNG || info->spec == PF_SPEC_LOCT
			|| info->mod == PF_MOD_L)
		arg->n = va_arg(ap, unsigned long);
	else if (info->mod == PF_MOD_LL)
		arg->n = va_arg(ap, unsigned long long);
	else if (info->mod == PF_MOD_H)
		arg->n = (unsigned short)va_arg(ap, unsigned int);
	else if (info->mod == PF_MOD_HH)
		arg->n = (unsigned char)va_arg(ap, unsigned int);
	else if (info->mod == PF_MOD_J)
		arg->n = va_arg(ap, uintmax_t);
	else if (info->mod == PF_MOD_Z)
		arg->n = va_arg(ap, size_t);
	else
		arg->n = va_arg(ap, unsigned int);
}

void	set_base(t_pf_int *arg, t_pf_info *info)
{
	if (info->spec == PF_SPEC_LHEX || info->spec == PF_SPEC_UHEX
			|| info->spec == PF_SPEC_ADDR)
		arg->base = 16;
	else if (info->spec == PF_SPEC_OCT || info->spec == PF_SPEC_LOCT)
		arg->base = 8;
	else if (info->spec == PF_SPEC_LBIN || info->spec == PF_SPEC_UBIN)
		arg->base = 2;
	else
		arg->base = 10;
	arg->upper_base = arg->base == 16 && info->spec == PF_SPEC_UHEX;
}

void	set_prefix(t_pf_int *arg, t_pf_info *info)
{
	if (info->spec == PF_SPEC_ADDR)
		ft_strcpy(arg->prefix, "0x");
	else if (PF_HAS_FLAG(info->flags, PF_FLAG_ALT))
	{
		if (info->spec == PF_SPEC_LHEX && arg->n != 0)
			ft_strcpy(arg->prefix, "0x");
		else if (info->spec == PF_SPEC_UHEX && arg->n != 0)
			ft_strcpy(arg->prefix, "0X");
		else if (info->spec == PF_SPEC_OCT || info->spec == PF_SPEC_LOCT)
			ft_strcpy(arg->prefix, "0");
		else if (info->spec == PF_SPEC_LBIN)
			ft_strcpy(arg->prefix, "0b");
		else if (info->spec == PF_SPEC_UBIN)
			ft_strcpy(arg->prefix, "0B");
	}
}

void	*pf_arg_uint(t_pf_info *info, va_list ap)
{
	t_pf_int	*arg;

	if (!(arg = (t_pf_int *)ft_memalloc(sizeof(*arg))))
		return (NULL);
	cast_arg(arg, info, ap);
	set_base(arg, info);
	set_prefix(arg, info);
	return ((void *)arg);
}
