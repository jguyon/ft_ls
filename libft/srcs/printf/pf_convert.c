/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 17:04:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 16:16:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "priv/pf_convert.h"
#include "priv/pf_parse.h"

#define SPECMIN ' '
#define SPECMAX '~'
#define SPECTOI(s) (s - SPECMIN)

static t_conv	*g_convs[SPECMAX - SPECMIN + 1] = {
	[SPECTOI(PF_CHAR_SPEC)] = &pf_convert_char,
	[SPECTOI(PF_STRING_SPEC)] = &pf_convert_str,
	[SPECTOI(PF_INT_SPEC)] = &pf_convert_int,
	[SPECTOI(PF_ALTINT_SPEC)] = &pf_convert_int,
	[SPECTOI(PF_UINT_SPEC)] = &pf_convert_uint,
	[SPECTOI(PF_OCT_SPEC)] = &pf_convert_uint,
	[SPECTOI(PF_HEXLO_SPEC)] = &pf_convert_uint,
	[SPECTOI(PF_HEXUP_SPEC)] = &pf_convert_uint,
	[SPECTOI(PF_ADDR_SPEC)] = &pf_convert_uint,
	[SPECTOI(PF_PTR_SPEC)] = &pf_convert_ptr,
};

int				pf_convert(t_stream *stream, t_pf_info *info, va_list args)
{
	if (info->spec >= SPECMIN && info->spec <= SPECMAX
		&& g_convs[SPECTOI(info->spec)])
		return (g_convs[SPECTOI(info->spec)](stream, info, args));
	return (-1);
}
