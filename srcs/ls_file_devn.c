/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_devn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:54:11 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 16:11:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_file_devn(struct stat *sb, char **maj, char **min)
{
	*maj = NULL;
	*min = NULL;
	if (!S_ISBLK(sb->st_mode) && !S_ISCHR(sb->st_mode))
		return (0);
	*maj = ft_uimtoa_base(LS_MAJOR(sb->st_rdev), 10, 0, 1);
	*min = ft_uimtoa_base(LS_MINOR(sb->st_rdev), 10, 0, 1);
	if (!(*min) || !(maj))
	{
		ft_memdel((void **)min);
		ft_memdel((void **)maj);
		return (0);
	}
	return (1);
}
