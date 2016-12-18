/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fopencookie.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:56:27 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 19:57:52 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftstream.h"

t_stream	*ft_fopencookie(void *cookie, t_stream_type type)
{
	t_stream	*stream;

	if (!(stream = ft_memalloc(sizeof(*stream))))
		return (NULL);
	stream->cookie = cookie;
	stream->type = type;
	stream->curr = stream->buff;
	return (stream);
}
