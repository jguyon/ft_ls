/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_uint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:13:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/18 00:13:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "ft_memory.h"
#include "ft_numbers.h"
#include "ft_strings.h"
#include "priv/pf_write.h"
#include "priv/pf_convert.h"

static uintmax_t	get_arg(t_pf_info *info, va_list args)
{
	if (info->spec == PF_ADDR_SPEC)
		return ((uintmax_t)va_arg(args, void *));
	else if (info->mod == HH)
		return ((unsigned char)va_arg(args, unsigned int));
	else if (info->mod == H)
		return ((unsigned short)va_arg(args, unsigned int));
	else if (info->mod == LL)
		return (va_arg(args, unsigned long long));
	else if (info->mod == L)
		return (va_arg(args, unsigned long));
	else if (info->mod == J)
		return (va_arg(args, uintmax_t));
	else if (info->mod == Z)
		return (va_arg(args, size_t));
	else
		return (va_arg(args, unsigned int));
}

static const char	*g_hexlo = "0x";
static const char	*g_hexup = "0X";
static const char	*g_oct = "0";
static const char	*g_uint = "";
static const char	*g_empty = "";

static const char	*get_prefix(t_pf_info *info)
{
	if (info->spec == PF_ADDR_SPEC)
		return (g_hexlo);
	if (!(info->flags.alt))
		return (g_empty);
	if (info->spec == PF_OCT_SPEC)
		return (g_oct);
	else if (info->spec == PF_HEXLO_SPEC)
		return (g_hexlo);
	else if (info->spec == PF_HEXUP_SPEC)
		return (g_hexup);
	else
		return (g_uint);
}

static int			get_base(t_pf_info *info)
{
	if (info->spec == PF_OCT_SPEC)
		return (8);
	else if (info->spec == PF_HEXLO_SPEC || info->spec == PF_ADDR_SPEC)
		return (16);
	else if (info->spec == PF_HEXUP_SPEC)
		return (-16);
	else
		return (10);
}

static int			write_uint(t_stream *stream, t_pf_info *info,
								const char *prefix, uintmax_t n)
{
	size_t	count;
	size_t	lenp;
	size_t	lenn;
	int		base;

	base = get_base(info);
	lenn = pf_uintmax_len(n, 0, PF_ABS(base));
	info->prec = info->prec < 0 ? 1 : info->prec;
	if (*prefix == '0' && *(prefix + 1) == '\0' && (size_t)info->prec > lenn)
		prefix = g_empty;
	lenn = (size_t)info->prec > lenn ? (size_t)info->prec : lenn;
	lenp = ft_strlen(prefix);
	if (info->flags.left || info->min_width < 0)
		count = pf_write_str(stream, prefix, lenp)
			+ pf_write_uint(stream, n, base, lenn)
			+ pf_write_pad(stream, ' ', PF_ABS(info->min_width), lenn + lenp);
	else if (info->flags.zero && info->prec < 0)
		count = pf_write_str(stream, prefix, lenp)
			+ pf_write_pad(stream, '0', info->min_width, lenn + lenp)
			+ pf_write_uint(stream, n, base, lenn);
	else
		count = pf_write_pad(stream, ' ', info->min_width, lenn + lenp)
			+ pf_write_str(stream, prefix, lenp)
			+ pf_write_uint(stream, n, base, lenn);
	return (ft_ferror(stream) ? -1 : (int)count);
}

int					pf_convert_uint(t_stream *stream, t_pf_info *info,
										va_list args)
{
	uintmax_t	n;
	const char	*prefix;
	int			res;

	n = get_arg(info, args);
	prefix = get_prefix(info);
	res = write_uint(stream, info, prefix, n);
	return (res);
}
