/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 18:25:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 12:51:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_WRITE_H
# define PF_WRITE_H

# include "ft_streams.h"

/*
** pf_write_pad - writes padding corresponding to a string
** @stream: stream to write to
** @c: padding character
** @min_len: min length of the string
** @real_len: actual length of the string
**
** Returns the number of bytes of padding written.
*/
size_t	pf_write_pad(t_stream *stream, char c, size_t min_len, size_t real_len);

/*
** pf_write_str - writes a string
** @stream: stream to write to
** @str: string to write
** @len: number of bytes to write
*/
size_t	pf_write_str(t_stream *stream, const char *str, size_t len);

/*
** pf_write_wstr - write a unicode string
** @stream: stream to write to
** @wstr: string to write
** @len: number of bytes to write
*/
size_t	pf_write_wstr(t_stream *stream, const wchar_t *wstr, size_t len);

#endif
