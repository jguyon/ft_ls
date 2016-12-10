/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:13:51 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 22:14:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static char		*g_null_str = "(null)";

static size_t	str_len(char *str, int prec)
{
	size_t	len;

	if (prec < 0)
		return (ft_strlen(str));
	len = 0;
	while ((int)len < prec && *str)
	{
		++len;
		++str;
	}
	return (len);
}

static size_t	wstr_len(wchar_t *wstr, int prec)
{
	size_t	len;

	if (prec < 0)
		return (ft_wstrlen(wstr));
	len = 0;
	while ((int)len < prec && *wstr != L'\0')
	{
		len += ft_wclen(*wstr);
		++wstr;
	}
	return ((int)len > prec ? (size_t)prec : len);
}

void			*pf_arg_str(t_pf_info *info, va_list ap)
{
	t_pf_str	*arg;

	if (!(arg = (t_pf_str *)ft_memalloc(sizeof(*arg))))
		return (NULL);
	if (info->spec == PF_SPEC_WSTR || info->mod == PF_MOD_L)
	{
		arg->wstr = va_arg(ap, wchar_t *);
		arg->len = arg->wstr ? wstr_len(arg->wstr, info->prec) : 0;
	}
	else
	{
		arg->str = va_arg(ap, char *);
		arg->len = arg->str ? str_len(arg->str, info->prec) : 0;
	}
	if (!(arg->str) && !(arg->wstr))
	{
		arg->str = g_null_str;
		arg->len = str_len(arg->str, info->prec);
	}
	return (arg);
}
