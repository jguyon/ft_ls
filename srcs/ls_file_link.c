/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_link.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 19:37:24 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 19:45:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_file_link(const char *path, struct stat *sb)
{
	ssize_t	r;
	char	*str;
	if (!(S_ISLNK(sb->st_mode)) || !(str = ft_strnew(sb->st_size + 1)))
		return (NULL);
	r = readlink(path, str, sb->st_size + 1);
	if (r < 0 || r > sb->st_size)
	{
		ft_memdel((void **)&str);
		return (NULL);
	}
	str[r] = '\0';
	return (str);
}
