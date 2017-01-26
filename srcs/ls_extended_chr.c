/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_extended_chr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 12:27:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 03:21:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_long_format.h"
#include <errno.h>
#include <sys/types.h>
#ifdef __APPLE__
# include <sys/acl.h>
# include <sys/xattr.h>
#elif linux
# include <acl/libacl.h>
#endif

#ifdef __APPLE__

char	ls_extended_chr(const char *path, mode_t mode)
{
	int		errnum;
	acl_t	acl;
	char	c;

	errnum = errno;
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		c = '@';
	else if (!S_ISLNK(mode) && (acl = acl_get_file(path, ACL_TYPE_EXTENDED)))
	{
		c = '+';
		acl_free(acl);
	}
	else
		c = ' ';
	errno = errnum;
	return (c);
}

#elif linux

char	ls_extended_chr(const char *path, mode_t mode)
{
	int		errnum;
	char	c;

	errnum = errno;
	if (!S_ISLNK(mode) && acl_extended_file(path) > 0)
		c = '+';
	else
		c = ' ';
	errno = errnum;
	return (c);
}

#endif
