/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:47:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 16:49:19 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include <errno.h>

int		ls_flist_init(t_flist *flist)
{
	FT_DLST_INIT(&(flist->dirs), t_file, node);
	FT_DLST_INIT(&(flist->files), t_file, node);
	if (!(flist->print))
	{
		errno = EINVAL;
		return (-1);
	}
	if (flist->init)
		flist->init(flist->dirinfo);
	return (0);
}
