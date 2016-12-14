/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_time.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:26:01 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 23:03:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_file_time(struct stat *sb)
{
	char	*str;
	char	*ct;
	time_t	now;

	if (!(ct = ctime(&(sb->st_mtime)))
		|| !(str = ft_strnew(13)))
		return (NULL);
	ft_strncpy(str, ct + 4, 6);
	str[6] = ' ';
	now = time(NULL);
	if (sb->st_mtime + ((365 / 2) * 24 * 3600) < now
		|| now + ((365 / 2) * 24 * 3600) < sb->st_mtime)
	{
		if (ft_strncmp("     ", ct + 19, 5) == 0)
			ft_strncpy(str + 7, ct + 23, 6);
		else
			ft_strncpy(str + 7, ct + 19, 5);
	}
	else
		ft_strncpy(str + 7, ct + 11, 5);
	return (str);
}
