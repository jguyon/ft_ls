/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:43:25 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 22:43:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static int			get_num(char **format)
{
	int		num;

	num = 0;
	while (**format >= '0' && **format <= '9')
	{
		num = 10 * num + (**format - '0');
		++(*format);
	}
	return (num);
}

static int			get_arg(char **format)
{
	char	*str;
	int		n;

	str = *format;
	n = get_num(&str);
	if (*str != PF_ARG_END || n == 0)
		return (0);
	*format = str + 1;
	return (n);
}

static unsigned int	get_flag(char **format)
{
	unsigned int	flag;

	flag = 0;
	if (**format == PF_CHAR_ALT)
		flag = PF_FLAG_ALT;
	else if (**format == PF_CHAR_ZRO)
		flag = PF_FLAG_ZRO;
	else if (**format == PF_CHAR_NEG)
		flag = PF_FLAG_NEG;
	else if (**format == PF_CHAR_SPC)
		flag = PF_FLAG_SPC;
	else if (**format == PF_CHAR_PLS)
		flag = PF_FLAG_PLS;
	if (flag)
		++(*format);
	return (flag);
}

static int			get_modifier(char **format)
{
	int		mod;

	if (ft_strncmp(*format, "ll", 2) == 0)
		mod = PF_MOD_LL;
	else if (ft_strncmp(*format, "hh", 2) == 0)
		mod = PF_MOD_HH;
	else if (**format == 'l')
		mod = PF_MOD_L;
	else if (**format == 'h')
		mod = PF_MOD_H;
	else if (**format == 'j')
		mod = PF_MOD_J;
	else if (**format == 'z')
		mod = PF_MOD_Z;
	else
		mod = 0;
	if (mod)
	{
		++(*format);
		if (mod == PF_MOD_HH || mod == PF_MOD_LL)
			++(*format);
	}
	return (mod);
}

t_pf_info			*pf_get_info(char **format)
{
	t_pf_info		*info;
	unsigned int	flag;

	++(*format);
	if (!(info = (t_pf_info *)ft_memalloc(sizeof(*info))))
		return (NULL);
	info->arg = get_arg(format);
	while ((flag = get_flag(format)))
		info->flags |= flag;
	info->width = **format == PF_ARG_START ? 0 : get_num(format);
	info->width_arg = **format == PF_ARG_START && ++(*format)
						? get_arg(format) : -1;
	info->prec = -1;
	info->prec_arg = -1;
	if (**format == PF_PREC_START && ++(*format))
	{
		info->prec = **format == PF_ARG_START ? -1 : get_num(format);
		info->prec_arg = (**format == PF_ARG_START && ++(*format))
						? get_arg(format) : -1;
	}
	info->mod = get_modifier(format);
	info->spec = **format;
	++(*format);
	return (info);
}
