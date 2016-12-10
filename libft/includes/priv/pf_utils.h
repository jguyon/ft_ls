/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 21:55:07 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:05:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_UTILS_H
# define PF_UTILS_H

# include "libftprintf.h"
# include <unistd.h>

/*
** FORMAT PARSING
*/

# define PF_FORMAT_START '%'

# define PF_ARG_START '*'
# define PF_ARG_END '$'

# define PF_SPEC_COUNT	19
# define PF_SPEC_INT	'd'
# define PF_SPEC_AINT	'i'
# define PF_SPEC_LNG	'D'
# define PF_SPEC_UINT	'u'
# define PF_SPEC_ULNG	'U'
# define PF_SPEC_LHEX	'x'
# define PF_SPEC_UHEX	'X'
# define PF_SPEC_OCT	'o'
# define PF_SPEC_LOCT	'O'
# define PF_SPEC_LBIN	'b'
# define PF_SPEC_UBIN	'B'
# define PF_SPEC_ADDR	'p'
# define PF_SPEC_STR	's'
# define PF_SPEC_CHAR	'c'
# define PF_SPEC_UNPS	'r'
# define PF_SPEC_WSTR	'S'
# define PF_SPEC_WCHAR	'C'
# define PF_SPEC_PTR	'n'
# define PF_SPEC_FMT	'%'

# define PF_FLAG_ALT 0b00001
# define PF_FLAG_ZRO 0b00010
# define PF_FLAG_NEG 0b00100
# define PF_FLAG_SPC 0b01000
# define PF_FLAG_PLS 0b10000

# define PF_CHAR_ALT '#'
# define PF_CHAR_ZRO '0'
# define PF_CHAR_NEG '-'
# define PF_CHAR_SPC ' '
# define PF_CHAR_PLS '+'

# define PF_HAS_FLAG(flags, test) ((int)(flags & test))
# define PF_ALL_FLAGS(flags, test) ((int)(flags & test == test))

# define PF_PREC_START '.'

# define PF_MOD_HH	1
# define PF_MOD_H	2
# define PF_MOD_L	3
# define PF_MOD_LL	4
# define PF_MOD_J	5
# define PF_MOD_Z	6

typedef struct	s_pf_info {
	size_t			arg;
	char			spec;
	unsigned int	flags : 5;
	int				width;
	ssize_t			width_arg;
	int				prec;
	ssize_t			prec_arg;
	int				mod;
	int				count;
}				t_pf_info;

typedef struct	s_pf_format {
	char	spec;
	void	*(*get_arg)(t_pf_info *info, va_list ap);
	int		(*format)(t_stream *stream, t_pf_info *info, void *arg);
	void	(*clean_arg)(void **arg);
}				t_pf_format;

typedef struct	s_pf_conv {
	const char			*prev;
	size_t				len;
	t_pf_info			*info;
	t_pf_format			*format;
	void				*arg;
}				t_pf_conv;

typedef struct	s_pf_conv_acc {
	int			count;
	t_stream	*stream;
}				t_pf_conv_acc;

typedef struct	s_pf_arg {
	size_t		n;
	t_pf_conv	*conv;
	int			type;
}				t_pf_arg;

t_list			*pf_parse_format(const char *format);
int				pf_extract_args(t_list *convs, va_list ap);
int				pf_write_convs(t_stream *stream, t_list *convs);
void			pf_del_convs(t_list **convs);

t_pf_info		*pf_get_info(char **format);
t_pf_format		*pf_get_format(t_pf_info *info);

/*
** ARG FORMATTING
*/

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
