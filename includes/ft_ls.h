/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 21:22:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libftstream.h"
# include "libftprintf.h"

# define LS_CHAR_LNG 'l'
# define LS_CHAR_REC 'R'
# define LS_CHAR_ALL 'a'
# define LS_CHAR_REV 'r'
# define LS_CHAR_TME 't'
# define LS_CHAR_FLAG '-'

# define LS_FLAG_LNG 1
# define LS_FLAG_REC 2
# define LS_FLAG_ALL 4
# define LS_FLAG_REV 8
# define LS_FLAG_TME 16

# define LS_ADD_FLAG(flags, f) (flags |= f)
# define LS_HAS_FLAG(flags, f) (flags & f)

typedef struct	s_ls_args {
	char			*cmd;
	unsigned int	flags : 5;
	t_list			*files;
}				t_ls_args;

t_ls_args		*ls_parse_args(int ac, char **av);
void			ls_destroy_args(t_ls_args **args);

#endif
