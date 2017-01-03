/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fopencookie.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:56:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 21:17:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_streams.h"

t_stream	*ft_fopencookie(void *cookie, t_stream_type type)
{
	t_stream	*stream;

	if (type.buff_size == 0
		|| !(stream = ft_memalloc(sizeof(*stream)))
		|| !(stream->buff = (char *)ft_memalloc(type.buff_size)))
		return (NULL);
	stream->cookie = cookie;
	stream->type = type;
	stream->curr = stream->buff;
	return (stream);
}
