/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:00:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 20:36:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_FORMAT_H
# define LS_FORMAT_H

/*
** Format and output file information
*/

# include "ls_cache.h"
# include <sys/stat.h>
# include <stddef.h>
# include <limits.h>

/*
** Print directory name
*/
void			ls_print_dir(const char *name);

/*
** Print file in line format
*/
void			ls_print_line(const char *name);

/*
** Macros to extract major and minor device numbers from a dev_t number
*/
# ifdef __APPLE__
#  define LS_MAJOR(d) (((dev_t)(d) >> (sizeof(dev_t) * 8 - 8)) & 0xffu)
#  define LS_MINOR(d) ((dev_t)(d) & 0xffu)
# elif linux
#  define LS_MAJOR(d) (((dev_t)(d) >> 8) & 0xffu)
#  define LS_MINOR(d) ((dev_t)(d) & 0xffu)
# endif

/*
** Six months in type time_t
*/
# define LS_SIX_MONTHS ((time_t)((366 / 2) * 24 * 3600))

/*
** Structure holding total size and max lengths of a group of files
*/
typedef struct	s_dinfo {
	int			has_files;
	size_t		total;
	size_t		max_nlink;
	size_t		max_owner;
	size_t		max_group;
	size_t		max_size;
	size_t		max_maj;
	size_t		max_min;
}				t_dinfo;

/*
** Update @info using @st for long format
*/
void			ls_update_info(t_dinfo *info, struct stat *st);

/*
** Print total block count of files
*/
void			ls_print_total(t_dinfo *info);

/*
** Print file in long format
**
** Returns -1 if some non-blocking error occurred, 0 otherwise.
*/
int				ls_print_long(const char *name, const char *path,
								t_dinfo *info, struct stat *st);

/*
** Print mode string
*/
void			ls_print_mode(mode_t mode);

/*
** Print number of links
*/
void			ls_print_nlink(nlink_t nlink, size_t width);

/*
** Print owner and group
*/
void			ls_print_pwd(uid_t uid, size_t uid_width,
								gid_t gid, size_t gid_width);

/*
** Print number of blocks
*/
void			ls_print_blocks(blkcnt_t blocks, size_t blk_width,
								size_t maj_width, size_t min_width);

/*
** Print device numbers
*/
void			ls_print_dev(dev_t dev, size_t blk_width,
								size_t maj_width, size_t min_width);

/*
** Print last modification time
*/
void			ls_print_time(time_t time);

/*
** Print link target
*/
void			ls_print_target(const char *path, off_t size);

/*
** Structure used to cache calls to getpwuid
*/
typedef struct	s_owner {
	uid_t			uid;
	size_t			len;
	t_dlist_node	node;
	char			name[];
}				t_owner;

/*
** Cache holding owner names
**
** Call ls_cache_clear on it at the end of the program.
*/
t_cache			g_ls_owners;

/*
** Get owner name corresponding to @uid
*/
const char		*ls_get_owner(uid_t uid);

/*
** Structure used to cache calls to getgrgid
*/
typedef struct	s_group {
	gid_t			gid;
	t_dlist_node	node;
	char			name[];
}				t_group;

/*
** Cache holding group names
**
** Call ls_cache_clear on it at the end of the program.
*/
t_cache			g_ls_groups;

/*
** Get group name corresponding to @gid
*/
const char		*ls_get_group(gid_t gid);

#endif
