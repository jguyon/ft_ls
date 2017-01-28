/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_callbacks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:21:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/28 19:01:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CALLBACKS_H
# define LS_CALLBACKS_H

/*
** Callbacks to use with t_flist structures
*/

# include "ls_files.h"

/*
** Exit status of the program
*/
int				g_ls_status;

/*
** Colors corresponding to each type of file
*/
# define LS_COLOR_RESET	"\x1B[0m"
# define LS_COLOR_DIR	"\x1B[0;34m"
# define LS_COLOR_LNK	"\x1B[0;35m"
# define LS_COLOR_SOCK	"\x1B[0;32m"
# define LS_COLOR_FIFO	"\x1B[0;33m"
# define LS_COLOR_EXEC	"\x1B[0;31m"
# define LS_COLOR_BLK	"\x1B[0;34;46m"
# define LS_COLOR_CHR	"\x1B[0;34;42m"
# define LS_COLOR_XUID	"\x1B[0;30;41m"
# define LS_COLOR_XGID	"\x1B[0;30;46m"
# define LS_COLOR_OTHS	"\x1B[0;30;42m"
# define LS_COLOR_OTHD	"\x1B[0;30;43m"

/*
** Assign 1 if stat is needed for all files
*/
int				g_need_lstat;

/*
** Initialize this with one of the functions below to
** configure which file time is used
**
** Set to ls_get_mtime by default.
*/
struct timespec	*(*g_get_time)(struct stat *st);

struct timespec	*ls_get_mtime(struct stat *st);
struct timespec	*ls_get_ctime(struct stat *st);
struct timespec	*ls_get_atime(struct stat *st);

/*
** Initialize this with one of the functions below to
** configure how file names are displayed
**
** Set to ls_name_normal by default.
** Returns -1 on error, 0 otherwise.
*/
int				(*g_print_name)(t_file *file);

int				ls_name_normal(t_file *file);
int				ls_name_color(t_file *file);

/*
** Initialize this with one of the functions below to
** print a suffix after the name
**
** Set to null by default.
** Returns -1 on error, 0 if no suffix was printed, 1 otherwise.
*/
int				(*g_print_suffix)(t_file *file);

int				ls_suffix_type(t_file *file);
int				ls_suffix_dir(t_file *file);

/*
** Print the error represented by errno
*/
void			ls_file_error(const char *name);

/*
** Prepare the stat of a file if needed
**
** This should be the default flist insert callback
*/
int				ls_insert_lstat(void *dirinfo, t_file *file);

/*
** Hide hidden files or implied '.' and '..'
*/
int				ls_reject_hidden(const char *name);
int				ls_reject_implied(const char *name);

/*
** Comparison functions for sorting
*/
int				ls_compare_lexi(t_file *f1, t_file *f2);
int				ls_compare_time(t_file *f1, t_file *f2);
int				ls_compare_size(t_file *f1, t_file *f2);

/*
** Print the name of a file and a newline
*/
int				ls_print_line(void *dirinfo, t_file *file);

/*
** Struct and callbacks used for long format
*/

typedef struct	s_long_dinfo {
	int		has_files;
	size_t	total;
	size_t	max_nlink;
	size_t	max_owner;
	size_t	max_group;
	size_t	max_size;
	size_t	max_maj;
	size_t	max_min;
}				t_long_dinfo;

typedef struct	s_long_finfo {
	char			extended;
	const char		*owner;
	const char		*group;
	char			mode[11];
	char			time[13];
	char			target[];
}				t_long_finfo;

void			ls_init_long(t_long_dinfo *dinfo);
int				ls_insert_long(t_long_dinfo *dinfo, t_file *file);
int				ls_print_long(t_long_dinfo *dinfo, t_file *file);
void			ls_print_total(t_long_dinfo *dinfo);

/*
** Struct and callbacks used for column format
*/

typedef struct	s_cols_dinfo {
	size_t		count;
	size_t		colwidth;
	size_t		cols;
	size_t		rows;
	size_t		last;
	size_t		x;
	size_t		y;
}				t_cols_dinfo;

void			ls_init_cols(t_cols_dinfo *dinfo);
int				ls_insert_cols(t_cols_dinfo *dinfo, t_file *file);
void			ls_prepare_cols(t_cols_dinfo *dinfo, t_dlist *files, int rev);
int				ls_print_cols(t_cols_dinfo *dinfo, t_file *file);

#endif
