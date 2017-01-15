/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fwrite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:02:35 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 15:20:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_streams.h"

static size_t	stream_write(const char *buff, size_t count, t_stream *stream)
{
	size_t	res;

	res = stream->funs.write(stream->cookie, buff, count);
	if (res != count)
		stream->err = 1;
	return (res);
}

size_t			ft_fwrite(const char *s, size_t count, t_stream *stream)
{
	size_t	i;
	size_t	size;

	if (!stream || !(stream->funs.write) || ft_ferror(stream)
		|| (!(stream->buff) && stream->size > 0 && ft_fflush(stream) < 0))
		return (0);
	if (stream->size == 0)
		return (stream_write(s, count, stream));
	i = count;
	while (i)
	{
		size = stream->size - (stream->curr - stream->buff);
		if (i < size)
			size = i;
		ft_memcpy(stream->curr, s, size);
		stream->curr += size;
		if (i > size && ft_fflush(stream) < 0)
			break ;
		s += size;
		i -= size;
	}
	return (count - i);
}
