/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setbuffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:24:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 19:24:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"

int		ft_setbuffer(t_stream *stream, char *buff, size_t size)
{
	if (!stream || stream->buff || (!buff && size == 0))
		return (-1);
	stream->buff = buff;
	stream->size = size;
	stream->curr = stream->buff;
	return (0);
}
