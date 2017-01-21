/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:57:05 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 15:45:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_memory.h"

t_file	*ls_file_new(t_flags flags, const char *name, const char *path,
						int need_stat)
{
	t_file	*file;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
		return (NULL);
	if ((need_stat || flags.sorting == LS_SORT_TIME
			|| flags.format == LS_FORMAT_LONG)
		&& lstat(path ? path : name, &(file->stat)))
	{
		ft_memdel((void **)&file);
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
	if (flags.format == LS_FORMAT_LONG)
		ls_set_finfo(&(file->info), path ? path : name, file->time->tv_sec,
						&(file->stat));
	if (file->stat.st_mode != 0)
		file->is_dir = S_ISDIR(file->stat.st_mode);
	return (file);
}
