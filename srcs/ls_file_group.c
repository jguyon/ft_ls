/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:14:36 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/27 15:50:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_file_group(struct stat *sb)
{
	static t_ls_fgroup	groups[LS_CACHE_SIZE] = {{LS_CACHE_EMPTY, {0}}};
	struct group		*grp;
	size_t				index;

	index = sb->st_gid % LS_CACHE_SIZE;
	if (groups[index].status == LS_CACHE_EMPTY)
	{
		if ((grp = getgrgid(sb->st_gid)))
		{
			ft_strncpy(groups[index].name, grp->gr_name, LS_GROUP_LEN);
			groups[index].status = LS_CACHE_VALID;
		}
		else
			groups[index].status = LS_CACHE_INVALID;
	}
	if (groups[index].status == LS_CACHE_VALID)
		return (ft_strdup(groups[index].name));
	else
		return (ft_uimtoa_base(sb->st_gid, 10, 0, 1));
}
