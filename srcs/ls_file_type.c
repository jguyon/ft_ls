/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:56:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 15:08:44 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include <errno.h>

int		ls_file_ltype(t_file *file)
{
	if (!file)
	{
		errno = EINVAL;
		return (-1);
	}
	if (file->ltype != LS_FTYP_UNKNOWN)
		return (0);
	return (ls_file_lstat(file));
}

int		ls_file_type(t_file *file)
{
	if (!file)
	{
		errno = EINVAL;
		return (-1);
	}
	if (file->type != LS_FTYP_UNKNOWN)
		return (0);
	if (file->ltype != LS_FTYP_UNKNOWN && file->ltype != LS_FTYP_LNK)
	{
		file->type = file->ltype;
		return (0);
	}
	return (ls_file_stat(file));
}
