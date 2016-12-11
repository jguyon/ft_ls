/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 17:56:39 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/11 19:26:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*create_file(const char *dirname, struct dirent *entry)
{
	t_list		*el;
	t_ls_file	file;

	if (!(file.name = ft_strnew(entry->d_namlen))
		|| !(file.stat = ft_memalloc(sizeof(*(file.stat)))))
	{
		ft_memdel((void **)&(file.name));
		return (NULL);
	}
	ft_strncpy(file.name, entry->d_name, entry->d_namlen);
	file.path = NULL;
	if (!(file.path = ft_strnew(entry->d_namlen + 1 + ft_strlen(dirname)))
		|| !(ft_strcpy(file.path, dirname))
		|| !(ft_strcat(file.path, "/"))
		|| !(ft_strcat(file.path, entry->d_name))
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

static int	fcmp(t_list *e1, t_list *e2)
{
	t_ls_file	*f1;
	t_ls_file	*f2;

	f1 = (t_ls_file *)(e1->content);
	f2 = (t_ls_file *)(e2->content);
	return (ft_strcmp(f1->name, f2->name) > 0);
}

t_list	*ls_list_files(unsigned int flags, const char *dirname)
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
		if (entry->d_name[0] != '.' && (el = create_file(dirname, entry)))
			ft_lstadd(&files, el);
	}
	closedir(dir);
	(void)flags;
	ft_lstsort(&files, &fcmp);
	return (files);
}
