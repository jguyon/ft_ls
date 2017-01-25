/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_callbacks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:21:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 14:06:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CALLBACKS_H
# define LS_CALLBACKS_H

# include "ls_files.h"

# define LS_EXIT_STATUS g_ls_status
int		g_ls_status;

void	ls_file_error(const char *name);

int		ls_insert_lstat(void *dirinfo, t_file *file);

int		ls_reject_hidden(t_file *file);

# ifdef __APPLE__
#  define LS_MNSEC(stat) ((stat)->st_mtimespec.tv_nsec)
#  define LS_CNSEC(stat) ((stat)->st_ctimespec.tv_nsec)
#  define LS_ANSEC(stat) ((stat)->st_atimespec.tv_nsec)
# elif linux
#  define LS_MNSEC(stat) ((stat)->st_mtim.tv_nsec)
#  define LS_CNSEC(stat) ((stat)->st_ctim.tv_nsec)
#  define LS_ANSEC(stat) ((stat)->st_atim.tv_nsec)
# endif

int		ls_compare_lexi(t_file *f1, t_file *f2);
int		ls_compare_mtim(t_file *f1, t_file *f2);
int		ls_compare_ctim(t_file *f1, t_file *f2);
int		ls_compare_atim(t_file *f1, t_file *f2);
int		ls_compare_size(t_file *f1, t_file *f2);

int		ls_print_line(void *dirinfo, t_file *file);

#endif
