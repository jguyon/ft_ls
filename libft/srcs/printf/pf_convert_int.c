/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 11:23:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 19:12:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "ft_numbers.h"
#include "ft_strings.h"
#include "priv/pf_write.h"
#include "priv/pf_convert.h"

static const char	*g_neg = "-";
static const char	*g_pls = "+";
static const char	*g_spc = " ";
static const char	*g_pos = "";

static const char	*get_prefix(int is_neg, t_pf_flags flags)
{
	if (is_neg)
		return (g_neg);
	else if (flags.plus)
		return (g_pls);
	else if (flags.space)
		return (g_spc);
	else
		return (g_pos);
}

static int			write_int(t_stream *stream, t_pf_info *info,
								const char *prefix, uintmax_t n)
{
	size_t	count;
	size_t	lenp;
	size_t	lenn;

	lenp = ft_strlen(prefix);
	lenn = pf_uintmax_len(n, info->prec, 10);
	if (info->flags.left || info->min_width < 0)
		count = pf_write_str(stream, prefix, lenp)
			+ pf_write_uint(stream, n, 10, lenn)
			+ pf_write_pad(stream, ' ', PF_ABS(info->min_width), lenn + lenp);
	else if (info->flags.zero && info->prec < 0)
		count = pf_write_str(stream, prefix, lenp)
			+ pf_write_pad(stream, '0', info->min_width, lenn + lenp)
			+ pf_write_uint(stream, n, 10, lenn);
	else
		count = pf_write_pad(stream, ' ', info->min_width, lenn + lenp)
			+ pf_write_str(stream, prefix, lenp)
			+ pf_write_uint(stream, n, 10, lenn);
	if (ft_ferror(stream))
		return (-1);
	return ((int)count);
}

int					pf_convert_int(t_stream *stream, t_pf_info *info,
									va_list args)
{
	intmax_t	n;
	const char	*prefix;
	int			res;

	if (info->mod == HH)
		n = (signed char)va_arg(args, int);
	else if (info->mod == H)
		n = (short)va_arg(args, int);
	else if (info->mod == L)
		n = va_arg(args, long);
	else if (info->mod == LL)
		n = va_arg(args, long long);
	else if (info->mod == J)
		n = va_arg(args, intmax_t);
	else if (info->mod == Z)
		n = va_arg(args, ssize_t);
	else
		n = va_arg(args, int);
	prefix = get_prefix(n < 0, info->flags);
	res = write_int(stream, info, prefix, PF_ABS(n));
	return (res);
}
