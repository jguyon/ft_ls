/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:57:05 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 16:42:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_memory.h"

t_file	*alloc_file(int alloc_stat, int alloc_info)
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

t_file	*ls_file_new(t_flags flags, const char *name, const char *path,
						int need_stat)
{
	t_file	*file;

	file = alloc_file(need_stat
						|| flags.format == LS_FORMAT_LONG
						|| flags.sorting == LS_SORT_TIME,
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
	if (file->info)
		ls_set_finfo(file->info, path ? path : name, file->time->tv_sec,
						file->stat);
	if (file->stat)
		file->is_dir = S_ISDIR(file->stat->st_mode);
	return (file);
}
