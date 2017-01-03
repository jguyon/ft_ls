/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fclose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:07:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 22:11:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_streams.h"

int		ft_fclose(t_stream *stream)
{
	int		res;

	if (!stream || !(stream->curr))
		return (-1);
	ft_fflush(stream);
	res = stream->type.close ? stream->type.close(stream->cookie) : 0;
	res = ft_ferror(stream) ? -1 : res;
	ft_memdel((void **)&(stream->buff));
	ft_memdel((void **)&stream);
	return (res);
}
