/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 20:31:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 12:20:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** Main logic of ft_ls
*/

# include "ft_dlists.h"
# include <sys/stat.h>

/*
** Macros and structure for parsing opts given to the program
*/

# define LS_FLAGS "Ralrt1"

# define LS_FLAG_ALL	'a'
# define LS_FLAG_LFMT	'l'
# define LS_FLAG_MTIM	't'
# define LS_FLAG_REV	'r'
# define LS_FLAG_REC	'R'

# define LS_USAGE_FMT "usage: %s [-%s] [file ...]\n"

typedef struct	s_flags {
	unsigned char	all : 1;
	unsigned char	lfmt : 1;
	unsigned char	mtim : 1;
	unsigned char	rev : 1;
	unsigned char	rec : 1;
}				t_flags;

/*
** Structure for listing files
*/

typedef struct	s_file {
	const char		*name;
	const char		*path;
	t_dlist_node	node;
	struct stat		stat;
}				t_file;

/*
** Structure holding parsed arguments
*/

typedef struct	s_args {
	t_flags		flags;
	t_dlist		dirs;
	t_dlist		files;
}				t_args;

/*
** Parse command line arguments
**
** Returns 1 if successful, 0 if not.
*/
int				ls_parse_args(int argc, char *const argv[], t_args *args);

/*
** List files in a directory
*/
void			ls_list_files(t_flags flags, t_file *dir, t_dlist *files);

#endif
