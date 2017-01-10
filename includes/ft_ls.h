/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 20:31:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 21:04:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** Main logic of ft_ls
*/

/*
** Macros and structure for parsing opts given to the program
*/

# define LS_FLAGS "altrR"

# define LS_FLAG_ALL	'a'
# define LS_FLAG_LFMT	'l'
# define LS_FLAG_MTIM	't'
# define LS_FLAG_REV	'r'
# define LS_FLAG_REC	'R'

typedef struct	s_flags {
	unsigned char	all : 1;
	unsigned char	lfmt : 1;
	unsigned char	mtim : 1;
	unsigned char	rev : 1;
	unsigned char	rec : 1;
}				t_flags;

/*
** Parse flags from command line options
**
** Returns 1 if successful, 0 if not.
*/
int				ls_parse_flags(int argc, char *const argv[], t_flags *flags);

#endif
