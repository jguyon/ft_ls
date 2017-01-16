/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_update_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:22:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 19:16:03 by jguyon           ###   ########.fr       */
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

void			ls_update_info(t_dinfo *info, struct stat *st)
{
	const char	*str;

	info->has_files = 1;
	info->total += st->st_blocks;
	info->max_nlink = sze_max(info->max_nlink, uim_len(st->st_nlink));
	if ((str = ls_get_owner(st->st_uid)))
		info->max_owner = sze_max(info->max_owner, ft_strlen(str));
	else
		info->max_owner = sze_max(info->max_owner, uim_len(st->st_uid));
	if ((str = ls_get_group(st->st_gid)))
		info->max_group = sze_max(info->max_group, ft_strlen(str));
	else
		info->max_group = sze_max(info->max_group, uim_len(st->st_gid));
	if (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode))
	{
		info->max_maj = sze_max(info->max_maj, uim_len(LS_MAJOR(st->st_dev)));
		info->max_min = sze_max(info->max_min, uim_len(LS_MINOR(st->st_dev)));
	}
	else
		info->max_size = sze_max(info->max_size, uim_len(st->st_size));
}
