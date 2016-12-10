/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftstream.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:50:17 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 19:59:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSTREAM_H
# define LIBFTSTREAM_H

# include "libft.h"

# define FT_BUFF_SIZE 4096

typedef struct	s_stream_type {
	size_t	(*write)(void *cookie, const char *buff, size_t size);
	int		(*close)(void *cookie);
}				t_stream_type;

typedef struct	s_stream {
	void			*cookie;
	char			*curr;
	t_stream_type	type;
	char			buff[FT_BUFF_SIZE];
}				t_stream;

t_stream		*ft_fopencookie(void *cookie, t_stream_type type);
size_t			ft_fwrite(const char *s, size_t count, t_stream *stream);
int				ft_fputc(int c, t_stream *stream);
int				ft_fputs(const char *s, t_stream *stream);
int				ft_ferror(t_stream *stream);
int				ft_fclose(t_stream *stream);
int				ft_fflush(t_stream *stream);

#endif
