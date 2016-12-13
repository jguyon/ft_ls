/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_owner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:06:46 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 21:13:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_file_owner(struct stat *sb)
{
	struct passwd	*pw;

	errno = 0;
	if ((pw = getpwuid(sb->st_uid)))
		return (ft_strdup(pw->pw_name));
	else if (errno != 0)
		return (NULL);
	else
		return (ft_uimtoa_base(sb->st_uid, 10, 0, 1));
}
