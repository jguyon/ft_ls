/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 20:31:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/22 07:28:34 by jguyon           ###   ########.fr       */
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

# define LS_FLAGS "ARSacdfglnortu1"

# define LS_FLAG_ALL	'a'
# define LS_FLAG_ALMOST	'A'
# define LS_FLAG_LFMT	'l'
# define LS_FLAG_GRP	'g'
# define LS_FLAG_USR	'o'
# define LS_FLAG_NUM	'n'
# define LS_FLAG_TIME	't'
# define LS_FLAG_SIZE	'S'
# define LS_FLAG_REV	'r'
# define LS_FLAG_REC	'R'
# define LS_FLAG_NODIR	'd'
# define LS_FLAG_LINE	'1'
# define LS_FLAG_ATIM	'u'
# define LS_FLAG_CTIM	'c'
# define LS_FLAG_NOSRT	'f'

# define LS_USAGE_FMT "usage: %s [-%s] [file ...]\n"

typedef enum	e_format {
	LS_FORMAT_LINE = 0,
	LS_FORMAT_LONG = 1,
}				t_format;

typedef enum	e_sorting {
	LS_SORT_LEXI = 0,
	LS_SORT_TIME = 1,
	LS_SORT_SIZE = 2,
	LS_SORT_NONE = 3,
}				t_sorting;

typedef enum	e_time {
	LS_TIME_MODIF = 0,
	LS_TIME_ACCESS = 1,
	LS_TIME_CHANGE = 2,
}				t_time;

typedef enum	e_show {
	LS_SHOW_NOHIDDEN = 0,
	LS_SHOW_ALMOST = 1,
	LS_SHOW_ALL = 2,
}				t_show;

typedef enum	e_bool {
	LS_BOOL_FALSE = 0,
	LS_BOOL_TRUE = 1
}				t_bool;

typedef struct	s_flags {
	t_format		format : 1;
	t_bool			noowner : 1;
	t_bool			nogroup : 1;
	t_bool			numeric : 1;
	t_bool			reverse : 1;
	t_show			show : 2;
	t_bool			recur : 1;
	t_bool			nodirs : 1;
	t_sorting		sorting : 2;
	t_time			time : 2;
}				t_flags;

/*
** Structure for listing files
*/

typedef struct	s_file {
	int				is_dir;
	const char		*name;
	const char		*path;
	struct timespec	*time;
	t_dlist_node	node;
	struct stat		*stat;
	t_finfo			*info;
}				t_file;

/*
** Get pointer to timespec
*/
# ifdef linux
#  define LS_MTIM(st) (&((st)->st_mtim))
#  define LS_ATIM(st) (&((st)->st_atim))
#  define LS_CTIM(st) (&((st)->st_ctim))
# elif __APPLE__
#  define LS_MTIM(st) (&((st)->st_mtimespec))
#  define LS_ATIM(st) (&((st)->st_atimespec))
#  define LS_CTIM(st) (&((st)->st_ctimespec))
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

/*
** Parse one flag
*/
void			ls_parse_flag(t_flags *flags, int opt);

/*
** Create file, allocating only what is needed according to @flags
**
** If @need_stat is 1, the stat structure will always be filled.
*/
t_file			*ls_file_new(t_flags flags, const char *name, const char *path,
								int need_stat);

#endif
