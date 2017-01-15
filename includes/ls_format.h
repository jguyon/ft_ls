/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:00:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 20:58:41 by jguyon           ###   ########.fr       */
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
** Print file in line format
*/
int				ls_print_line(const char *name);

/*
** Macros to extract major and minor device numbers from a dev_t number
*/
# ifdef __APPLE__
#  define LS_MAJOR(d) (((d) >> (sizeof(dev_t) * 8 - 8)) & 0xff)
#  define LS_MINOR(d) ((d) & 0xff)
# elif linux
#  define LS_MAJOR(d) (((d) >> 8) & 0xff)
#  define LS_MINOR(d) ((d) & 0xff)
# endif

/*
** Structure holding total size and max lengths of a group of files
*/
typedef struct	s_dinfo {
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
**
** Returns 1 if successful, 0 if not.
*/
void			ls_update_info(t_dinfo *info, struct stat *st);

/*
** Print file in long format
*/
int				ls_print_long(const char *name, t_dinfo *info, struct stat *st);

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
