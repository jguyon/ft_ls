/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 21:49:24 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/31 16:17:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ls_join_path(const char *dirname, const char *filename)
{
	char	*path;
	size_t	len;

	len = ft_strlen(dirname);
	if (len == 0)
		return (ft_strdup(filename));
	else if (dirname[len - 1] == '/')
		return (ft_strjoin(dirname, filename));
	else if ((path = ft_strnew(len + 1 + ft_strlen(filename))))
	{
		ft_strcpy(path, dirname);
		path[len] = '/';
		ft_strcpy(path + len + 1, filename);
		return (path);
	}
	return (NULL);
}
