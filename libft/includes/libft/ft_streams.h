/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streams.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:17:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 21:16:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STREAMS_H
# define FT_STREAMS_H

# include <stddef.h>

# define FT_BUFF_SIZE 4096

typedef struct	s_stream_type {
	size_t	buff_size;
	size_t	(*write)(void *cookie, const char *buff, size_t size);
	int		(*close)(void *cookie);
}				t_stream_type;

typedef struct	s_stream {
	void			*cookie;
	char			*curr;
	t_stream_type	type;
	char			*buff;
}				t_stream;

t_stream		*ft_fopencookie(void *cookie, t_stream_type type);
size_t			ft_fwrite(const char *s, size_t count, t_stream *stream);
int				ft_fputc(int c, t_stream *stream);
int				ft_fputs(const char *s, t_stream *stream);
int				ft_ferror(t_stream *stream);
int				ft_fclose(t_stream *stream);
int				ft_fflush(t_stream *stream);

#endif
