/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fopencookie.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:56:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 19:50:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_streams.h"

t_stream	*ft_fopencookie(void *cookie, t_stream_funs funs)
{
	t_stream	*stream;

	if (!(stream = (t_stream *)ft_memalloc(sizeof(*stream))))
		return (NULL);
	stream->funs = funs;
	stream->cookie = cookie;
	stream->size = FT_BUFF_SIZE;
	stream->alloc = 1;
	return (stream);
}
