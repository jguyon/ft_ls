/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:59:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 04:09:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_parse.h"
#include "libft/ft_printf.h"

int		ft_vfprintf(t_stream *stream, const char *format, va_list ap)
{
	t_list		*convs;
	int			count;

	if (format
			&& !(ft_ferror(stream))
			&& (convs = pf_parse_format(format))
			&& pf_extract_args(convs, ap))
		count = pf_write_convs(stream, convs);
	else
		count = -1;
	pf_del_convs(&convs);
	return (count);
}
