/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_stat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 14:15:53 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 15:05:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include <errno.h>
#include <stdlib.h>

static t_ftype	file_type(struct stat *st)
{
	if (S_ISFIFO(st->st_mode))
		return (LS_FTYP_FIFO);
	else if (S_ISCHR(st->st_mode))
		return (LS_FTYP_CHR);
	else if (S_ISDIR(st->st_mode))
		return (LS_FTYP_DIR);
	else if (S_ISBLK(st->st_mode))
		return (LS_FTYP_BLK);
	else if (S_ISLNK(st->st_mode))
		return (LS_FTYP_LNK);
	else if (S_ISSOCK(st->st_mode))
		return (LS_FTYP_SOCK);
	else if (S_ISWHT(st->st_mode))
		return (LS_FTYP_WHT);
	else
		return (LS_FTYP_REG);
}

int				ls_file_lstat(t_file *file)
{
	struct stat	*st;

	if (!file || !(file->path))
	{
		errno = EINVAL;
		return (-1);
	}
	if (file->lstat)
		return (0);
	if (!((st = (struct stat *)malloc(sizeof(*st))))
		|| lstat(file->path, st))
	{
		free(st);
		return (-1);
	}
	if (file->ltype == LS_FTYP_UNKNOWN)
		file->ltype = file_type(st);
	file->lstat = st;
	return (0);
}

int				ls_file_stat(t_file *file)
{
	struct stat	*st;

	if (!file || !(file->path))
	{
		errno = EINVAL;
		return (-1);
	}
	if (file->stat)
		return (0);
	if (file->lstat && !S_ISLNK(file->lstat->st_mode))
	{
		file->stat = file->lstat;
		return (0);
	}
	if (!(st = (struct stat *)malloc(sizeof(*stat)))
		|| stat(file->path, st))
	{
		free(st);
		return (-1);
	}
	if (file->type == LS_FTYP_UNKNOWN)
		file->type = file_type(st);
	file->stat = st;
	return (0);
}
