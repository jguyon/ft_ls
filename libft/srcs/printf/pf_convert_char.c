/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 14:41:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 14:58:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_unicode.h"
#include "priv/pf_write.h"
#include "priv/pf_convert.h"

static size_t	write_char(t_stream *stream, t_pf_info *info, char c)
{
	size_t	count;

	if (info->flags.left || info->min_width < 0)
		count = pf_write_str(stream, &c, 1)
			+ pf_write_pad(stream, ' ', PF_ABS(info->min_width), 1);
	else
		count = pf_write_pad(stream, ' ', info->min_width, 1)
			+ pf_write_str(stream, &c, 1);
	return (count);
}

static size_t	write_wchar(t_stream *stream, t_pf_info *info, wchar_t c)
{
	size_t	count;
	size_t	len;

	len = ft_wclen(c);
	if (info->flags.left || info->min_width < 0)
		count = pf_write_wstr(stream, &c, len)
			+ pf_write_pad(stream, ' ', PF_ABS(info->min_width), len);
	else
		count = pf_write_pad(stream, ' ', info->min_width, len)
			+ pf_write_wstr(stream, &c, len);
	return (count);
}

int				pf_convert_char(t_stream *stream, t_pf_info *info,
									va_list args)
{
	size_t	count;

	if (info->mod == L)
		count = write_wchar(stream, info, va_arg(args, wint_t));
	else
		count = write_char(stream, info, (char)va_arg(args, int));
	if (ft_ferror(stream))
		return (-1);
	return ((int)count);
}
