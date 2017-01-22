/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:57:05 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/22 08:27:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_memory.h"

static t_file	*alloc_file(int alloc_stat, int alloc_info)
{
	t_file	*file;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file)))
		|| (alloc_stat &&
			!(file->stat = (struct stat *)ft_memalloc(sizeof(*(file->stat)))))
		|| (alloc_info &&
			!(file->info = (t_finfo *)ft_memalloc(sizeof(*(file->info))))))
	{
		ls_destroy_file(file);
		return (NULL);
	}
	return (file);
}

static void		set_info(t_flags flags, t_finfo *info, t_file *file)
{
	info->extended = ls_extended_chr(file->path, file->stat->st_mode);
	info->time = file->time->tv_sec;
	info->stat = file->stat;
	if (!(info->no_owner = flags.noowner) && !(flags.numeric))
		info->owner = ls_get_owner(file->stat->st_uid);
	if (!(info->no_group = flags.nogroup) && !(flags.numeric))
		info->group = ls_get_group(file->stat->st_gid);
}

t_file			*ls_file_new(t_flags flags, const char *name, const char *path,
								int need_stat)
{
	t_file	*file;

	file = alloc_file(need_stat || flags.format == LS_FORMAT_LONG
						|| flags.sorting == LS_SORT_TIME
						|| flags.sorting == LS_SORT_SIZE,
						flags.format == LS_FORMAT_LONG);
	if (!file || (file->stat && lstat(path ? path : name, file->stat)))
	{
		ls_destroy_file(file);
		return (NULL);
	}
	file->name = name;
	file->path = path;
	if (flags.time == LS_TIME_ACCESS)
		file->time = LS_ATIM(file->stat);
	else if (flags.time == LS_TIME_CHANGE)
		file->time = LS_CTIM(file->stat);
	else
		file->time = LS_MTIM(file->stat);
	if (file->stat)
		file->is_dir = S_ISDIR(file->stat->st_mode);
	if (file->info)
		set_info(flags, file->info, file);
	return (file);
}
