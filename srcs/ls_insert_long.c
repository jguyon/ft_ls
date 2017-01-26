/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_insert_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 21:59:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 02:08:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ls_long_format.h"
#include "ft_memory.h"
#include "ft_strings.h"

#define MAX(n1, n2) (n1 > n2 ? n1 : n2)

static void			del_finfo(void *finfo)
{
	ft_memdel(&finfo);
}

static size_t		uim_len(uintmax_t n)
{
	size_t	len;

	len = 1;
	while ((n /= 10))
		++len;
	return (len);
}

static void			update_dinfo(t_long_dinfo *dinfo, t_file *file)
{
	dinfo->has_files = 1;
	dinfo->total += file->lstat->st_blocks;
	dinfo->max_nlink = MAX(dinfo->max_nlink, uim_len(file->lstat->st_nlink));
	dinfo->max_owner = ((t_long_finfo *)file->info)->owner
		? MAX(dinfo->max_owner, ft_strlen(((t_long_finfo *)file->info)->owner))
		: MAX(dinfo->max_owner, uim_len(file->lstat->st_uid));
	dinfo->max_group = ((t_long_finfo *)file->info)->group
		? MAX(dinfo->max_group, ft_strlen(((t_long_finfo *)file->info)->group))
		: MAX(dinfo->max_group, uim_len(file->lstat->st_gid));
	if (file->ltype == LS_FTYP_BLK || file->ltype == LS_FTYP_CHR)
	{
		dinfo->max_maj = MAX(dinfo->max_maj,
			uim_len(LS_MAJOR(file->lstat->st_rdev)));
		dinfo->max_min = MAX(dinfo->max_min,
							 uim_len(LS_MINOR(file->lstat->st_rdev)));
	}
	else
		dinfo->max_size = MAX(dinfo->max_size, uim_len(file->lstat->st_size));
}

static t_long_finfo	*get_info(t_file *file)
{
	t_long_finfo	*finfo;
	size_t			len;

	len = file->ltype == LS_FTYP_LNK ? ls_target_size(file->lstat) : 0;
	if (!(finfo = (t_long_finfo *)ft_memalloc(sizeof(*finfo) + len + 1))
		|| (file->ltype == LS_FTYP_LNK
			&& ls_read_target(finfo->target, file->path, len))
		|| ls_format_time(finfo->time, file->lstat->st_mtime))
	{
		ft_memdel((void **)&finfo);
		return (NULL);
	}
	ls_format_mode(finfo->mode, file->lstat->st_mode);
	finfo->extended = ls_extended_chr(file->path, file->lstat->st_mode);
	finfo->owner = ls_get_owner(file->lstat->st_uid);
	finfo->group = ls_get_group(file->lstat->st_gid);
	return (finfo);
}

int					ls_insert_long(t_long_dinfo *dinfo, t_file *file)
{
	file->del = &del_finfo;
	if (ls_file_lstat(file) || ls_file_ltype(file))
		return (-1);
	if (dinfo)
	{
		if (!(file->info = get_info(file)))
			return (-1);
		update_dinfo(dinfo, file);
	}
	return (0);
}
