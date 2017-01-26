/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_callbacks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:21:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 02:24:35 by jguyon           ###   ########.fr       */
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
** Get the nanosecond part of a timestamp
*/
# ifdef __APPLE__
#  define LS_MNSEC(stat) ((stat)->st_mtimespec.tv_nsec)
#  define LS_CNSEC(stat) ((stat)->st_ctimespec.tv_nsec)
#  define LS_ANSEC(stat) ((stat)->st_atimespec.tv_nsec)
# elif linux
#  define LS_MNSEC(stat) ((stat)->st_mtim.tv_nsec)
#  define LS_CNSEC(stat) ((stat)->st_ctim.tv_nsec)
#  define LS_ANSEC(stat) ((stat)->st_atim.tv_nsec)
# endif

/*
** Comparison functions for sorting
*/
int				ls_compare_lexi(t_file *f1, t_file *f2);
int				ls_compare_mtim(t_file *f1, t_file *f2);
int				ls_compare_ctim(t_file *f1, t_file *f2);
int				ls_compare_atim(t_file *f1, t_file *f2);
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
