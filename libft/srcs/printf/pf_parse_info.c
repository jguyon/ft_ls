/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 16:55:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 15:29:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_memory.h"
#include "ft_chars.h"
#include "priv/pf_parse.h"

static ssize_t	read_number(const char **format, va_list args)
{
	size_t	nbr;

	if (**format == PF_ARG_CHAR)
	{
		++(*format);
		return ((ssize_t)va_arg(args, int));
	}
	nbr = 0;
	while (ft_isdigit(**format))
	{
		nbr = 10 * nbr + (**format - '0');
		++(*format);
	}
	return (nbr);
}

static int		read_flag(const char *format, t_pf_flags *flags)
{
	if (*format == PF_FLAG_ALT)
		flags->alt = 1;
	else if (*format == PF_FLAG_ZERO)
		flags->zero = 1;
	else if (*format == PF_FLAG_LEFT)
		flags->left = 1;
	else if (*format == PF_FLAG_PLUS)
		flags->plus = 1;
	else if (*format == PF_FLAG_SPACE)
		flags->space = 1;
	else
		return (0);
	return (1);
}

static size_t	read_modifier(const char *format, t_mod *mod)
{
	if (*format == PF_MOD_L && *(format + 1) == PF_MOD_L)
		*mod = LL;
	else if (*format == PF_MOD_L)
		*mod = L;
	else if (*format == PF_MOD_H && *(format + 1) == PF_MOD_H)
		*mod = HH;
	else if (*format == PF_MOD_H)
		*mod = H;
	else if (*format == PF_MOD_J)
		*mod = J;
	else if (*format == PF_MOD_Z)
		*mod = Z;
	else
		*mod = NO_MOD;
	if (*mod == NO_MOD)
		return (0);
	if (*mod == LL || *mod == HH)
		return (2);
	return (1);
}

const char		*pf_parse_info(const char *format, t_pf_info *info,
								size_t count, va_list args)
{
	if (!(*format))
		return (NULL);
	ft_bzero(info, sizeof(*info));
	while (read_flag(format, &(info->flags)))
		++format;
	info->min_width = read_number(&format, args);
	info->prec = -1;
	if (*format == PF_PREC_PREFIX)
	{
		++format;
		info->prec = read_number(&format, args);
	}
	format += read_modifier(format, &(info->mod));
	info->spec = *(format++);
	info->count = count;
	return (format);
}
