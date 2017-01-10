/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_uint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:13:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 15:20:15 by jguyon           ###   ########.fr       */
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

static char			*get_nstr(uintmax_t n, t_pf_info *info)
{
	if (info->spec == PF_OCT_SPEC)
		return (ft_uimtoa_base(n, 8, 0, info->prec));
	else if (info->spec == PF_HEXLO_SPEC || info->spec == PF_ADDR_SPEC)
		return (ft_uimtoa_base(n, 16, 0, info->prec));
	else if (info->spec == PF_HEXUP_SPEC)
		return (ft_uimtoa_base(n, 16, 1, info->prec));
	else
		return (ft_uimtoa_base(n, 10, 0, info->prec));
}

static int			write_uint(t_stream *stream, t_pf_info *info,
								const char *prefix, const char *ns)
{
	size_t	count;
	size_t	lenp;
	size_t	lenn;

	if (!ns)
		return (-1);
	if (*prefix == '0' && *(prefix + 1) == '\0' && *ns == '0')
		prefix = g_empty;
	lenp = ft_strlen(prefix);
	lenn = ft_strlen(ns);
	if (info->flags.left || info->min_width < 0)
		count = pf_write_str(stream, prefix, lenp)
			+ pf_write_str(stream, ns, lenn)
			+ pf_write_pad(stream, ' ', PF_ABS(info->min_width), lenn + lenp);
	else if (info->flags.zero && info->prec < 0)
		count = pf_write_str(stream, prefix, lenp)
			+ pf_write_pad(stream, '0', info->min_width, lenn + lenp)
			+ pf_write_str(stream, ns, lenn);
	else
		count = pf_write_pad(stream, ' ', info->min_width, lenn + lenp)
			+ pf_write_str(stream, prefix, lenp)
			+ pf_write_str(stream, ns, lenn);
	if (ft_ferror(stream))
		return (-1);
	return ((int)count);
}

int					pf_convert_uint(t_stream *stream, t_pf_info *info,
										va_list args)
{
	uintmax_t	n;
	char		*str;
	const char	*prefix;
	int			res;

	n = get_arg(info, args);
	str = get_nstr(n, info);
	prefix = get_prefix(info);
	res = write_uint(stream, info, prefix, str);
	ft_memdel((void **)&str);
	return (res);
}
