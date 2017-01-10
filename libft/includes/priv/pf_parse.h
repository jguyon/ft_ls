/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 16:20:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 15:30:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_PARSE_H
# define PF_PARSE_H

# include <stdarg.h>
# include "ft_streams.h"
# include "priv/pf_defs.h"

/*
** pf_parse_info - parse conversion string
** @format: format string starting with the conversion
** @info: structure to write info to
** @args: arguments given to printf
**
** Returns the next character after the format string,
** or null if an error occurred.
*/
const char	*pf_parse_info(const char *format, t_pf_info *info,
							size_t count, va_list args);

/*
** pf_convert - convert and write
** @info - conversion info
** @args - arguments given to printf
**
** Returns the number of bytes written if successful,
** a negative number otherwise.
*/
int			pf_convert(t_stream *stream, t_pf_info *info, va_list args);

#endif
