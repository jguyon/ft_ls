/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:31:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:31:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** Formatted output functions
**
** These functions return the number of bytes written if successful,
** a negative number otherwise.
*/

# include <stdarg.h>
# include "ft_streams.h"

/*
** ft_printf - print formatted string to stdout
** @format: format to print
** @rest: arguments referenced by @format
*/
int		ft_printf(const char *format, ...);

/*
** ft_vprintf - va_list variant of ft_printf
*/
int		ft_vprintf(const char *format, va_list ap);

/*
** ft_dprintf - print formatted string to a file
** @fd: file descriptor
** @format: format to print
** @rest: arguments referenced by @format
*/
int		ft_dprintf(int fd, const char *format, ...);

/*
** ft_vdprintf - va_list variant of ft_dprintf
*/
int		ft_vdprintf(int fd, const char *format, va_list ap);

/*
** ft_fprintf - print formatted string to a stream
** @stream: stream to print to
** @format: format to print
** @rest: arguments referenced by @format
*/
int		ft_fprintf(t_stream *stream, const char *format, ...);

/*
** ft_vfprintf - va_list variant of ft_fprintf
*/
int		ft_vfprintf(t_stream *stream, const char *format, va_list ap);

#endif
