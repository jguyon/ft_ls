/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:00:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 22:02:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

void	*pf_arg_char(t_pf_info *info, va_list ap)
{
	t_pf_str	*arg;
	wchar_t		wc;

	if (!(arg = (t_pf_str *)ft_memalloc(sizeof(*arg))))
		return (NULL);
	if (info->spec == PF_SPEC_WCHAR || info->mod == PF_MOD_L)
	{
		wc = (wchar_t)va_arg(ap, wint_t);
		if ((arg->wstr = (wchar_t *)ft_memalloc(sizeof(*(arg->wstr)))))
			arg->wstr[0] = wc;
		arg->len = ft_wclen(wc);
	}
	else
	{
		if ((arg->str = (char *)ft_memalloc(sizeof(*(arg->str)))))
			arg->str[0] = (unsigned char)va_arg(ap, int);
		arg->len = 1;
	}
	if (!(arg->str) && !(arg->wstr))
		ft_memdel((void **)&arg);
	return (arg);
}
