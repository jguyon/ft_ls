/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 17:56:39 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 00:21:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*create_file(const char *dirname, struct dirent *entry)
{
	t_list		*el;
	t_ls_file	file;

	file.name = NULL;
	file.path = NULL;
	file.stat = NULL;
	if (!(file.name = ft_strdup(entry->d_name))
		|| !(file.path = ls_join_path(dirname, file.name))
		|| !(file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat))))
		|| lstat(file.path, file.stat)
		|| !(el = ft_lstnew(&file, sizeof(file))))
	{
		ls_printf_err(errno, "%s", file.path);
		ft_memdel((void **)&(file.name));
		ft_memdel((void **)&(file.path));
		ft_memdel((void **)&(file.stat));
		return (NULL);
	}
	return (el);
}

t_list			*ls_list_files(unsigned int flags, const char *dirname)
{
	DIR				*dir;
	t_list			*files;
	struct dirent	*entry;
	t_list			*el;

	files = NULL;
	if (!(dir = opendir(dirname)))
	{
		ls_printf_err(errno, "%s", dirname);
		return (NULL);
	}
	while ((entry = readdir(dir)))
	{
		if ((LS_HAS_FLAG(flags, LS_FLAG_ALL) || entry->d_name[0] != '.')
			&& (el = create_file(dirname, entry)))
			ft_lstadd(&files, el);
	}
	closedir(dir);
	ft_lstsort(&files, ls_sort_fun(flags));
	return (files);
}
