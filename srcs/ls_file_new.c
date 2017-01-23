/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:57:05 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 12:25:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_memory.h"
#include <unistd.h>

static struct stat	*get_stat(const char *path)
{
	struct stat	*st;

	if (!(st = (struct stat *)ft_memalloc(sizeof(*st))))
		return (NULL);
	if (lstat(path, st))
	{
		ft_memdel((void **)&st);
		return (NULL);
	}
	return (st);
}

static int			get_target(char *dst, const char *path, size_t len)
{
	ssize_t	res;

	res = readlink(path, dst, len + 1);
	if (res < 0 || (size_t)res > len)
		return (0);
	dst[res] = '\0';
	return (1);
}

static t_finfo		*get_info(t_flags flags, const char *path, time_t time,
								struct stat *st)
{
	t_finfo	*info;
	size_t	target_len;

	if (!S_ISLNK(st->st_mode))
		target_len = 0;
	else
		target_len = st->st_size > 0 ? st->st_size : PATH_MAX;
	if (!(info = (t_finfo *)ft_memalloc(sizeof(*info) + target_len + 1)))
		return (NULL);
	if (S_ISLNK(st->st_mode) && !get_target(info->target, path, target_len))
	{
		ft_memdel((void **)&info);
		return (NULL);
	}
	info->extended = ls_extended_chr(path, st->st_mode);
	info->time = time;
	info->stat = st;
	if (!(info->no_owner = flags.noowner) && !(flags.numeric))
		info->owner = ls_get_owner(st->st_uid);
	if (!(info->no_group = flags.nogroup) && !(flags.numeric))
		info->group = ls_get_group(st->st_gid);
	return (info);
}

struct timespec		*get_time(t_flags flags, struct stat *st)
{
	if (!st)
		return (NULL);
	if (flags.time == LS_TIME_ACCESS)
		return (LS_ATIM(st));
	else if (flags.time == LS_TIME_CHANGE)
		return (LS_CTIM(st));
	else
		return (LS_MTIM(st));
}

t_file				*ls_file_new(t_flags flags, const char *name,
									const char *path, int need_stat)
{
	t_file	*file;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
		return (NULL);
	if ((need_stat || flags.format == LS_FORMAT_LONG
			|| flags.sorting == LS_SORT_TIME || flags.sorting == LS_SORT_SIZE)
		&& !(file->stat = get_stat(path ? path : name)))
	{
		ft_memdel((void **)&file);
		return (NULL);
	}
	file->time = get_time(flags, file->stat);
	if (flags.format == LS_FORMAT_LONG
		&& !(file->info = get_info(flags, path ? path : name,
									file->time->tv_sec, file->stat)))
	{
		ft_memdel((void **)&(file->stat));
		ft_memdel((void **)&file);
		return (NULL);
	}
	file->name = name;
	file->path = path;
	if (file->stat)
		file->is_dir = S_ISDIR(file->stat->st_mode);
	return (file);
}
