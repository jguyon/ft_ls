/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:00:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/14 21:23:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_FORMAT_H
# define LS_FORMAT_H

/*
** Format and output file information
*/

# include <sys/stat.h>
# include <stddef.h>
# include <limits.h>

/*
** Max length of username
*/
# ifndef LOGIN_NAME_MAX
#  include <sys/param.h>
#  define LS_OWNER_MAX MAXLOGNAME
# else
#  define LS_OWNER_MAX LOGIN_NAME_MAX
# endif

/*
** Structure holding file info used for the long format
*/
typedef struct	s_finfo {
	char		mode[11];
	char		nlinks[sizeof(nlink_t) * 3 + 1];
	char		owner[LS_OWNER_MAX + 1];
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
** Cache size for owners and groups
**
** Must be a prime number to avoid collisions.
*/
# define LS_CACHE_SIZE 521

/*
** Structure used to cache calls to getpwuid
*/
typedef struct	s_owner {
	int			cached;
	uid_t		uid;
	size_t		len;
	char		owner[LS_OWNER_MAX + 1];
}				t_owner;

/*
** Set the owner name in @info from @st
**
** Returns the length of the string.
*/
size_t			ls_set_owner(t_finfo *info, struct stat *st);

#endif
