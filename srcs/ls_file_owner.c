/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_owner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:06:46 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/27 15:46:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_file_owner(struct stat *sb)
{
	static t_ls_fowner	owners[LS_CACHE_SIZE] = {{LS_CACHE_EMPTY, {0}}};
	struct passwd		*pw;
	size_t				index;

	index = sb->st_uid % LS_CACHE_SIZE;
	if (owners[index].status == LS_CACHE_EMPTY)
	{
		if ((pw = getpwuid(sb->st_uid)))
		{
			ft_strncpy(owners[index].name, pw->pw_name, LS_OWNER_LEN);
			owners[index].status = LS_CACHE_VALID;
		}
		else
			owners[index].status = LS_CACHE_INVALID;
	}
	if (owners[index].status == LS_CACHE_VALID)
		return (ft_strdup(owners[index].name));
	else
		return (ft_uimtoa_base(sb->st_uid, 10, 0, 1));
}
