/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_long_format.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:03:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/28 18:56:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_LONG_FORMAT_H
# define LS_LONG_FORMAT_H

/*
** Utilities for long format
*/

# include "ls_cache.h"
# include "ft_dlists.h"
# include <sys/stat.h>

/*
** Macros to extract major and minor device numbers
*/
# ifdef __APPLE__
#  define LS_MAJOR(d) (((dev_t)(d) >> (sizeof(dev_t) * 8 - 8)) & 0xffu)
#  define LS_MINOR(d) ((dev_t)(d) & 0xffu)
# elif linux
#  define LS_MAJOR(d) (((dev_t)(d) >> 8) & 0xffu)
#  define LS_MINOR(d) ((dev_t)(d) & 0xffu)
# endif

/*
** Six months as a timestamp
*/
# define LS_SIX_MONTHS ((time_t)((365 / 2) * 24 * 3600))

/*
** Structs used to cache owner and group names
*/

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

/*
** Caches for owners and groups
**
** ls_clear_cache should be called on them before program exit
*/
t_cache			g_ls_owners;
t_cache			g_ls_groups;

/*
** Obtain the name corresponding to a uid or gid
*/
const char		*ls_get_owner(uid_t uid);
const char		*ls_get_group(gid_t gid);

/*
** Format the type of file and its permissions
*/
void			ls_format_mode(char dst[10], mode_t mode);

/*
** Extract char representing whether the file has xattrs or acls
*/
char			ls_extended_chr(const char *path, mode_t mode);

/*
** Format the timestamp of a file
*/
int				ls_format_time(char dst[13], time_t time);

/*
** Get the name length of the target of a link and read its name
*/
size_t			ls_target_size(struct stat *st);
int				ls_read_target(char *dst, const char *path, size_t size);

#endif
