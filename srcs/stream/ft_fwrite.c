/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fwrite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:02:35 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 20:02:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftstream.h"

size_t	ft_fwrite(const char *s, size_t count, t_stream *stream)
{
	size_t	i;

	if (!stream || !(stream->curr) || !(stream->type.write))
		return (0);
	i = 0;
	while (i < count)
	{
		if (stream->curr - stream->buff >= FT_BUFF_SIZE)
		{
			if (stream->type.write(stream->cookie, stream->buff, FT_BUFF_SIZE)
					!= FT_BUFF_SIZE)
			{
				stream->curr = NULL;
				break ;
			}
			stream->curr = stream->buff;
		}
		*(stream->curr) = s[i];
		++(stream->curr);
		++i;
	}
	return (i);
}
