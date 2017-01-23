/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_update_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:22:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 19:38:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include "ft_printf.h"

static size_t	uim_len(uintmax_t n)
{
	size_t	len;

	len = 1;
	while ((n /= 10))
		++len;
	return (len);
}

static size_t	sze_max(size_t n1, size_t n2)
{
	return (n1 > n2 ? n1 : n2);
}

void			ls_update_long(t_dinfo *dinfo, t_finfo *finfo)
{
	dinfo->has_files = 1;
	dinfo->total += finfo->stat->st_blocks;
	dinfo->max_nlink = sze_max(dinfo->max_nlink,
								uim_len(finfo->stat->st_nlink));
	if (!(finfo->no_owner))
		dinfo->max_owner = finfo->owner
			? sze_max(dinfo->max_owner, ft_strlen(finfo->owner))
			: sze_max(dinfo->max_owner, uim_len(finfo->stat->st_uid));
	if (!(finfo->no_group))
		dinfo->max_group = finfo->group
			? sze_max(dinfo->max_group, ft_strlen(finfo->group))
		: sze_max(dinfo->max_group, uim_len(finfo->stat->st_gid));
	if (S_ISBLK(finfo->stat->st_mode) || S_ISCHR(finfo->stat->st_mode))
	{
		dinfo->max_maj = sze_max(dinfo->max_maj,
									uim_len(LS_MAJOR(finfo->stat->st_rdev)));
		dinfo->max_min = sze_max(dinfo->max_min,
									uim_len(LS_MINOR(finfo->stat->st_rdev)));
	}
	else
		dinfo->max_size = sze_max(dinfo->max_size,
									uim_len(finfo->stat->st_size));
}
