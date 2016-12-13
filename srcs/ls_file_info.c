/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 20:38:12 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 21:45:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t	max_len(size_t len1, size_t len2)
{
	return (len2 > len1 ? len2 : len1);
}

t_ls_finfo	*ls_file_info(const char *path, struct stat *sb, t_ls_dinfo *dinfo)
{
	t_ls_finfo	*finfo;

	if (!(finfo = (t_ls_finfo *)ft_memalloc(sizeof(*finfo)))
		|| !(finfo->mode = ls_file_mode(sb))
		|| !(finfo->links = ls_file_nlinks(sb))
		|| !(finfo->owner = ls_file_owner(sb))
		|| !(finfo->group = ls_file_group(sb))
		|| !(finfo->size = ls_file_size(sb))
		|| !(finfo->time = ls_file_time(sb))
		|| (S_ISLNK(sb->st_mode) && !(finfo->dest = ls_file_link(path, sb))))
	{
		ls_destroy_finfo(&finfo);
		return (NULL);
	}
	dinfo->total += sb->st_blocks;
	dinfo->max_lnk_len = max_len(dinfo->max_lnk_len, ft_strlen(finfo->links));
	dinfo->max_usr_len = max_len(dinfo->max_usr_len, ft_strlen(finfo->owner));
	dinfo->max_grp_len = max_len(dinfo->max_grp_len, ft_strlen(finfo->group));
	dinfo->max_sze_len = max_len(dinfo->max_sze_len, ft_strlen(finfo->size));
	return (finfo);
}
