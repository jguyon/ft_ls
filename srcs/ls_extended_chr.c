/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_extended_chr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 12:27:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 12:29:52 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include <errno.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>

char	ls_extended_chr(const char *path)
{
	int		errnum;
	acl_t	acl;
	char	c;

	errnum = errno;
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		c = '@';
	else if ((acl = acl_get_link_np(path, ACL_TYPE_EXTENDED)))
	{
		c = '+';
		acl_free(acl);
	}
	else
		c = ' ';
	errno = errnum;
	return (c);
}
