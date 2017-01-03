/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_info.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:49:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 12:04:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_INFO_H
# define PF_INFO_H

# include <stdlib.h>
# include <unistd.h>

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

#endif
