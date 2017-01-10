/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vfprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:50:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 21:07:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "priv/pf_parse.h"
#include "ft_printf.h"

/*
** We create an intermediary stream to defer writing until the end of the
** function if possible. This is advantageous with non-buffered streams
** like stderr and it avoids writing when a conversion error occurred.
*/

static size_t	buff_write(void *stm, const char *buff, size_t count)
{
	return (ft_fwrite(buff, count, stm));
}

static char		g_buff[FT_BUFF_SIZE];

static t_stream	g_stream = {
	.funs = {
		.write = &buff_write
	},
	.size = FT_BUFF_SIZE,
	.buff = g_buff,
	.curr = g_buff,
};

int				ft_vfprintf(t_stream *stream, const char *format, va_list args)
{
	size_t		count;
	int			res;
	char		*next;
	t_pf_info	info;

	if (!format || ft_ferror(stream))
		return (-1);
	g_stream.cookie = stream;
	count = 0;
	while ((next = ft_strchrnul(format, PF_CONV_PREFIX)))
	{
		count += (res = ft_fwrite(format, next - format, &g_stream));
		if (res != next - format || !(*(format = next)))
			break ;
		if (*(++format) == PF_CONV_PREFIX)
			count += ft_fwrite(format++, 1, &g_stream);
		else if ((format = pf_parse_info(format, &info, count, args)))
			count += (res = pf_convert(&g_stream, &info, args));
		if (res < 0 || !format || ft_ferror(&g_stream))
			break ;
	}
	if (res < 0 || !format || ft_fclose(&g_stream) || ft_ferror(stream))
		return (-1);
	return (count);
}
