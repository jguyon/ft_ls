/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:39:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 04:06:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_unicode.h"
#include "priv/pf_convert.h"

static int		write_unps(t_stream *stream, char *str, size_t len)
{
	int		i;

	i = 0;
	while (i < (int)len)
	{
		if (*str < ' ' || *str > '~')
			ft_fputc('.', stream);
		else
			ft_fputc(*str, stream);
		++str;
		++i;
	}
	return (i);
}

static int		write_str(t_stream *stream, t_pf_info *info, t_pf_str *arg)
{
	int		i;
	int		count;
	size_t	bytes;
	char	str[5];

	if (arg->str && info->spec == PF_SPEC_UNPS)
		return (write_unps(stream, arg->str, arg->len));
	else if (arg->str)
		return (ft_fwrite(arg->str, arg->len, stream));
	i = 0;
	count = 0;
	while ((size_t)count < arg->len)
	{
		if ((bytes = ft_wcconv(str, arg->wstr[i]))
						+ (size_t)count > arg->len)
			break ;
		count += ft_fwrite(str, bytes, stream);
		i++;
	}
	return (count);
}

static size_t	calc_wstrlen(t_pf_str *arg)
{
	size_t	i;
	size_t	bytes;
	size_t	len;

	i = 0;
	len = 0;
	while (len < arg->len)
	{
		if ((bytes = ft_wclen(arg->wstr[i])) + len > arg->len)
			break ;
		len += bytes;
		++i;
	}
	return (len);
}

static int		write_padding(t_stream *stream, t_pf_info *info, t_pf_str *arg)
{
	int		count;
	int		i;
	char	c;

	if (arg->wstr)
		i = calc_wstrlen(arg);
	else if (arg->str)
		i = arg->len;
	else
		return (0);
	c = (PF_HAS_FLAG(info->flags, PF_FLAG_ZRO)
			&& !PF_HAS_FLAG(info->flags, PF_FLAG_NEG))
		? '0' : ' ';
	count = 0;
	while (i < info->width)
	{
		ft_fputc(c, stream);
		++count;
		++i;
	}
	return (count);
}

int				pf_format_str(t_stream *stream, t_pf_info *info, void *arg)
{
	t_pf_str	*str_arg;
	int			count;

	str_arg = (t_pf_str *)arg;
	if (PF_HAS_FLAG(info->flags, PF_FLAG_NEG))
		count = write_str(stream, info, str_arg)
				+ write_padding(stream, info, str_arg);
	else
		count = write_padding(stream, info, str_arg)
				+ write_str(stream, info, str_arg);
	return (count);
}
