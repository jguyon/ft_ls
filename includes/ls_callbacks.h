/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_callbacks.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:21:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 23:43:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CALLBACKS_H
# define LS_CALLBACKS_H

# include "ls_files.h"
# include "ls_cache.h"

# define LS_EXIT_STATUS g_ls_status
int				g_ls_status;

void			ls_file_error(const char *name);

int				ls_insert_lstat(void *dirinfo, t_file *file);

int				ls_reject_hidden(t_file *file);
int				ls_reject_implied(t_file *file);

# ifdef __APPLE__
#  define LS_MNSEC(stat) ((stat)->st_mtimespec.tv_nsec)
#  define LS_CNSEC(stat) ((stat)->st_ctimespec.tv_nsec)
#  define LS_ANSEC(stat) ((stat)->st_atimespec.tv_nsec)
# elif linux
#  define LS_MNSEC(stat) ((stat)->st_mtim.tv_nsec)
#  define LS_CNSEC(stat) ((stat)->st_ctim.tv_nsec)
#  define LS_ANSEC(stat) ((stat)->st_atim.tv_nsec)
# endif

int				ls_compare_lexi(t_file *f1, t_file *f2);
int				ls_compare_mtim(t_file *f1, t_file *f2);
int				ls_compare_ctim(t_file *f1, t_file *f2);
int				ls_compare_atim(t_file *f1, t_file *f2);
int				ls_compare_size(t_file *f1, t_file *f2);

int				ls_print_line(void *dirinfo, t_file *file);

# ifdef __APPLE__
#  define LS_MAJOR(d) (((dev_t)(d) >> (sizeof(dev_t) * 8 - 8)) & 0xffu)
#  define LS_MINOR(d) ((dev_t)(d) & 0xffu)
# elif linux
#  define LS_MAJOR(d) (((dev_t)(d) >> 8) & 0xffu)
#  define LS_MINOR(d) ((dev_t)(d) & 0xffu)
# endif

# define LS_SIX_MONTHS ((time_t)((365 / 2) * 24 * 3600))

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

typedef struct	s_owner {
	uid_t			uid;
	size_t			len;
	t_dlist_node	node;
	char			name[];
}				t_owner;

typedef struct	s_group {
	gid_t			gid;
	t_dlist_node	node;
	char			name[];
}				t_group;

t_cache			g_ls_owners;
t_cache			g_ls_groups;

char			ls_extended_chr(const char *path, mode_t mode);
const char		*ls_get_owner(uid_t uid);
const char		*ls_get_group(gid_t gid);
void			ls_format_mode(char dst[10], mode_t mode);
int				ls_format_time(char dst[13], time_t time);
size_t			ls_target_size(struct stat *st);
int				ls_read_target(char *dst, const char *path, size_t size);

#endif
