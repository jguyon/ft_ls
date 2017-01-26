/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_callbacks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:21:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 11:31:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CALLBACKS_H
# define LS_CALLBACKS_H

/*
** Functions to use with a t_flist
*/

# include "ls_files.h"

/*
** Exit status of the program
*/
int				g_ls_status;

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
** Print the error represented by errno
*/
void			ls_file_error(const char *name);

/*
** Prepare the stat of a file for sorting by time or size
*/
int				ls_insert_lstat(void *dirinfo, t_file *file);

/*
** Hide hidden files or implied '.' and '..'
*/
int				ls_reject_hidden(t_file *file);
int				ls_reject_implied(t_file *file);

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
** Structs holding informations about a directory and its files
** for long format
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

/*
** Callbacks used for long format
*/
void			ls_init_long(t_long_dinfo *dinfo);
int				ls_insert_long(t_long_dinfo *dinfo, t_file *file);
int				ls_print_long(t_long_dinfo *dinfo, t_file *file);
void			ls_print_total(t_long_dinfo *dinfo);

#endif
