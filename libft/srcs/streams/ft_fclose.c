/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:07:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 19:50:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_streams.h"

int		ft_fclose(t_stream *stream)
{
	int		res;

	if (ft_fflush(stream) < 0)
		return (-1);
	res = stream->funs.close ? stream->funs.close(stream->cookie) : 0;
	res = ft_ferror(stream) ? -1 : res;
	if (stream->own)
		ft_memdel((void **)&(stream->buff));
	if (stream->alloc)
		ft_memdel((void **)&stream);
	return (res);
}
