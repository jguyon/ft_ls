/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_streams.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:17:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 18:21:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STREAMS_H
# define FT_STREAMS_H

/*
** Buffered output stream implementation
**
** /!\ Standard streams do not need to be opened,
** but they do need to be closed at the end of your program.
*/

# include <stddef.h>

/*
** FT_BUFF_SIZE - default buffer size of a stream
*/
# define FT_BUFF_SIZE 4096

/*
** t_stream_type - type containing functions used to flush or close the stream
*/
typedef struct	s_stream_funs {
	size_t	(*write)(void *cookie, const char *buff, size_t size);
	int		(*close)(void *cookie);
}				t_stream_funs;

/*
** t_stream - stream type
*/
typedef struct	s_stream {
	t_stream_funs	funs;
	void			*cookie;
	size_t			size;
	int				own;
	int				alloc;
	int				err;
	char			*curr;
	char			*buff;
}				t_stream;

/*
** FT_STDOUT - standard output stream
*/
t_stream		g_ft_stdout;
# define FT_STDOUT (&g_ft_stdout)

/*
** FT_STDERR - standard error stream
*/
t_stream		g_ft_stderr;
# define FT_STDERR (&g_ft_stderr)

/*
** ft_fopencookie - create a new stream
** @cookie: data passed to @type functions
** @type: description of the stream
*/
t_stream		*ft_fopencookie(void *cookie, t_stream_funs type);

/*
** ft_setbuffer - set the buffer of a stream
** @stream: stream to assign the buffer to
** @buff: buffer, must be at least @size bytes
** @size: size of the buffer
**
** Returns 0 on success, something else otherwise.
** Will always return an error if called after the first i/o operation.
*/
int				ft_setbuffer(t_stream *stream, char *buff, size_t size);

/*
** ft_fwrite - write characters to a stream
** @s: buffer of characters
** @count: number of bytes
** @stream: stream to write to
**
** Returns the number bytes written
*/
size_t			ft_fwrite(const char *s, size_t count, t_stream *stream);

/*
** ft_fputc - write a character to a stream
** @c: character to write
** @stream: stream to write to
**
** Returns the value written if successful, a negative number otherwise.
*/
int				ft_fputc(int c, t_stream *stream);

/*
** ft_fputs - write a string to a stream
** @s: string to write
** @stream: stream to write to
**
** Returns the number of bytes written if successful,
** a negative number otherwise.
*/
int				ft_fputs(const char *s, t_stream *stream);

/*
** ft_ferror - check if a stream has suffered an error
** @stream: stream to test
*/
int				ft_ferror(t_stream *stream);

/*
** ft_clearerr - clear stream error status
** @stream: stream to clear
*/
void			ft_clearerr(t_stream *stream);

/*
** ft_fclose - flush and close a stream
** @stream: stream to close
**
** Returns zero if successful, -1 otherwise.
*/
int				ft_fclose(t_stream *stream);

/*
** ft_fflush - flush buffer of a stream
** @stream - stream to flush
**
** Returns a zero if the buffer was empty, a positive number if flushing
** was successful, a negative number otherwise.
*/
int				ft_fflush(t_stream *stream);

#endif
