/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fflush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:08:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 15:21:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_streams.h"

int		ft_fflush(t_stream *stream)
{
	size_t	count;

	if (!stream || !(stream->funs.write) || ft_ferror(stream))
		return (-1);
	if (stream->size > 0 && !(stream->buff))
	{
		if (!(stream->buff = (char *)ft_memalloc(stream->size)))
			return (-1);
		stream->own = 1;
		stream->curr = stream->buff;
	}
	if (stream->size == 0 || stream->curr == stream->buff)
		return (0);
	count = stream->curr - stream->buff;
	if (stream->funs.write(stream->cookie, stream->buff, count) == count)
	{
		stream->curr = stream->buff;
		return (1);
	}
	stream->err = 1;
	return (-1);
}
