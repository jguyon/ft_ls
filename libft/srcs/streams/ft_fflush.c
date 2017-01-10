/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fflush.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:08:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 17:43:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_streams.h"

int		ft_fflush(t_stream *stream)
{
	if (!stream || !(stream->funs.write) || (stream->buff && !(stream->curr)))
		return (-1);
	if (!(stream->buff))
	{
		if (!(stream->buff = (char *)ft_memalloc(stream->size)))
			return (-1);
		stream->own = 1;
		stream->curr = stream->buff;
	}
	if (stream->curr == stream->buff)
		return (0);
	if (stream->funs.write(stream->cookie, stream->buff,
							stream->curr - stream->buff))
	{
		stream->curr = stream->buff;
		return (1);
	}
	stream->curr = NULL;
	return (-1);
}
