/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 20:31:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 16:50:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** Main logic of ft_ls
*/

# include "ft_dlists.h"
# include "ls_format.h"
# include <sys/stat.h>

/*
** Macro to get program exit status
*/
int				g_ls_status;
# define LS_EXIT_STATUS g_ls_status

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
	int				is_dir;
	t_dlist_node	node;
	struct stat		stat;
	t_finfo			info;
}				t_file;

/*
** Use nano seconds for time comparison if possible
*/
# ifdef linux
#  define LS_MTIM_NSEC(st) ((st).st_mtim.tv_nsec)
# elif __APPLE__
#  define LS_MTIM_NSEC(st) ((st).st_mtimespec.tv_nsec)
# else
#  define LS_MTIM_NSEC(st) (0)
# endif

/*
** Structure holding parsed arguments
*/

typedef struct	s_args {
	t_flags		flags;
	int			single;
	t_dinfo		dinfo;
	t_dlist		dirs;
	t_dlist		files;
}				t_args;

/*
** Parse command line arguments
*/
int				ls_parse_args(int argc, char *const argv[], t_args *args);

/*
** List files in a directory and initialize directory information
*/
void			ls_list_files(t_flags flags, t_file *dir,
								t_dinfo *dinfo, t_dlist *files);

/*
** Sort files according to given flags
*/
void			ls_sort_files(t_flags flags, t_dlist *files);

/*
** Pop next dir to process
*/
t_file			*ls_pop_next(t_flags flags, t_dlist *dirs);

/*
** Print name of directory and associated info
*/
void			ls_print_dirinfo(int is_single, t_flags flags,
									t_file *dir, t_dinfo *dinfo);

typedef struct	s_proginfo {
	t_flags		flags;
	t_dinfo		*dinfo;
}				t_proginfo;

/*
** Output files info in the correct format
**
** Puts dirs which need to be recursed over into @dirs, deletes and frees
** the rest.
*/
void			ls_print_files(t_flags flags, t_dlist *files, t_dinfo *dinfo,
								t_dlist *dirs);

/*
** Free file structure memory
*/
void			ls_destroy_file(t_file *file);

#endif
