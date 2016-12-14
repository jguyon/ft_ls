/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_group.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:14:36 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 17:55:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_file_group(struct stat *sb)
{
	struct group	*grp;

	if ((grp = getgrgid(sb->st_gid)))
		return (ft_strdup(grp->gr_name));
	else
		return (ft_uimtoa_base(sb->st_gid, 10, 0, 1));
}
