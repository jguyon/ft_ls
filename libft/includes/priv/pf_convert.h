/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:44:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 03:53:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_CONVERT_H
# define PF_CONVERT_H

# include <inttypes.h>
# include <stdarg.h>
# include "libft/ft_streams.h"
# include "priv/pf_info.h"

typedef struct	s_pf_int {
	uintmax_t		n;
	char			prefix[3];
	unsigned int	base;
	int				upper_base;
}				t_pf_int;

void			*pf_arg_int(t_pf_info *info, va_list ap);
void			*pf_arg_uint(t_pf_info *info, va_list ap);
int				pf_format_int(t_stream *stream, t_pf_info *info, void *arg);

typedef struct	s_pf_str {
	char		*str;
	wchar_t		*wstr;
	size_t		len;
}				t_pf_str;

void			*pf_arg_str(t_pf_info *info, va_list ap);
void			*pf_arg_char(t_pf_info *info, va_list ap);
void			*pf_arg_fmt(t_pf_info *info, va_list ap);
int				pf_format_str(t_stream *stream, t_pf_info *info, void *arg);
void			pf_clean_str(void **arg);

void			*pf_arg_ptr(t_pf_info *info, va_list ap);
int				pf_format_ptr(t_stream *stream, t_pf_info *info, void *arg);

#endif
