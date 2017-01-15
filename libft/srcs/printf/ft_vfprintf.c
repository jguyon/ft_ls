/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:50:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 15:08:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "priv/pf_parse.h"
#include "ft_printf.h"

/*
** If the stream is non-buffered, we create an intermediary stream
** to avoid repeated system calls to write a short amount of bytes.
*/

static size_t	buff_write(void *stm, const char *buff, size_t count)
{
	return (ft_fwrite(buff, count, stm));
}

static char		g_buff[FT_BUFF_SIZE];

static t_stream	g_buff_stream = {
	.funs = {
		.write = &buff_write
	},
	.size = FT_BUFF_SIZE,
	.buff = g_buff,
	.curr = g_buff,
};

static int		buff_vfprintf(t_stream *stream, const char *format, va_list args)
{
	int		res;

	g_buff_stream.cookie = stream;
	res = ft_vfprintf(&g_buff_stream, format, args);
	if (ft_fflush(&g_buff_stream) < 0)
		res = -1;
	return (res);
}

int				ft_vfprintf(t_stream *stream, const char *format, va_list args)
{
	size_t		count;
	int			res;
	char		*next;
	t_pf_info	info;

	if (!format || ft_ferror(stream))
		return (-1);
	if (stream->size == 0)
		return (buff_vfprintf(stream, format, args));
	count = 0;
	while ((next = ft_strchrnul(format, PF_CONV_PREFIX)))
	{
		count += (res = ft_fwrite(format, next - format, stream));
		if (res != next - format || !(*(format = next)))
			break ;
		if (*(++format) == PF_CONV_PREFIX)
			count += ft_fwrite(format++, 1, stream);
		else if ((format = pf_parse_info(format, &info, count, args)))
			count += (res = pf_convert(stream, &info, args));
		if (res < 0 || !format || ft_ferror(stream))
			break ;
	}
	if (res < 0 || !format || ft_ferror(stream))
		return (-1);
	return (count);
}
