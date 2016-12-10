/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:41:33 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 22:42:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static t_pf_format	g_formats[PF_SPEC_COUNT] = {
	{PF_SPEC_INT, &pf_arg_int, &pf_format_int, &ft_memdel},
	{PF_SPEC_AINT, &pf_arg_int, &pf_format_int, &ft_memdel},
	{PF_SPEC_LNG, &pf_arg_int, &pf_format_int, &ft_memdel},
	{PF_SPEC_UINT, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_ULNG, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_LHEX, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_UHEX, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_OCT, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_LOCT, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_LBIN, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_UBIN, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_ADDR, &pf_arg_uint, &pf_format_int, &ft_memdel},
	{PF_SPEC_STR, &pf_arg_str, &pf_format_str, &ft_memdel},
	{PF_SPEC_CHAR, &pf_arg_char, &pf_format_str, &pf_clean_str},
	{PF_SPEC_UNPS, &pf_arg_str, &pf_format_str, &ft_memdel},
	{PF_SPEC_WSTR, &pf_arg_str, &pf_format_str, &ft_memdel},
	{PF_SPEC_WCHAR, &pf_arg_char, &pf_format_str, &pf_clean_str},
	{PF_SPEC_PTR, &pf_arg_ptr, &pf_format_ptr, NULL},
	{PF_SPEC_FMT, &pf_arg_fmt, &pf_format_str, &pf_clean_str},
};

t_pf_format			*pf_get_format(t_pf_info *info)
{
	int		i;

	i = 0;
	while (i < PF_SPEC_COUNT)
	{
		if (g_formats[i].spec == info->spec)
			return (g_formats + i);
		++i;
	}
	return (NULL);
}
