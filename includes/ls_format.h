/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:00:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 00:59:18 by jguyon           ###   ########.fr       */
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
** Structure holding file info used for the long format
*/
typedef struct	s_finfo {
	char		mode[11];
	char		nlinks[sizeof(nlink_t) * 3 + 1];
	char		*owner;
	char		*group;
}				t_finfo;

/*
** Set mode string in @info from @st
*/
void			ls_set_mode(t_finfo *info, struct stat *st);

/*
** Set number of links string in @info from @st
**
** Returns the length of the string.
*/
size_t			ls_set_nlinks(t_finfo *info, struct stat *st);

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
** Set the owner name in @info from @st
**
** Returns the length of the string, or 0 in case of error.
*/
size_t			ls_set_owner(t_finfo *info, struct stat *st);

/*
** Structure used to cache calls to getgrgid
*/
typedef struct	s_group {
	gid_t			gid;
	size_t			len;
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
** Set the group name in @info from @st
**
** Returns the length of the string, or 0 in case of error.
*/
size_t			ls_set_group(t_finfo *info, struct stat *st);

#endif
