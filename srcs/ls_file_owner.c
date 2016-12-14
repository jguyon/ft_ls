/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_owner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:06:46 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 17:54:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_file_owner(struct stat *sb)
{
	struct passwd	*pw;

	if ((pw = getpwuid(sb->st_uid)))
		return (ft_strdup(pw->pw_name));
	else
		return (ft_uimtoa_base(sb->st_uid, 10, 0, 1));
}
