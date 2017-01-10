/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 17:26:22 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 15:33:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_CONVERT_H
# define PF_CONVERT_H

# include <stdarg.h>
# include "ft_streams.h"
# include "priv/pf_defs.h"

/*
** t_conv - conversion function type
** @stream: stream to write to
** @info: info for the conversion
** @args: arguments given to printf
*/
typedef int	(t_conv)(t_stream *stream, t_pf_info *info, va_list args);

/*
** All conversion functions
*/
int			pf_convert_char(t_stream *stream, t_pf_info *info, va_list args);
int			pf_convert_str(t_stream *stream, t_pf_info *info, va_list args);
int			pf_convert_int(t_stream *stream, t_pf_info *info, va_list args);
int			pf_convert_uint(t_stream *stream, t_pf_info *info, va_list args);
int			pf_convert_ptr(t_stream *stream, t_pf_info *info, va_list args);

#endif
