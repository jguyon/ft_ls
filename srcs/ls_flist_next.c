/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:31:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 18:01:13 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include "ft_memory.h"
#include "ft_strings.h"

static t_file	*new_file(const char *path, struct dirent *entry)
{
	t_file	*file;
	size_t	dlen;
	size_t	flen;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
		return (NULL);
	dlen = ft_strlen(path);
	if (path[dlen - 1] == '/')
		--dlen;
	flen = ft_strlen(entry->d_name);
	if ((file->path = ft_strnew(dlen + 1 + flen)))
	{
		ft_memcpy(file->path, path, dlen);
		file->path[dlen] = '/';
		ft_memcpy(file->path + dlen + 1, entry->d_name, flen);
		file->name = file->path + dlen + 1;
	}
	else
		ls_file_del(&file);
	return (file);
}

static void		list_files(const char *path, DIR *dir, t_flist *flist)
{
	struct dirent	*entry;
	t_file			*file;

	while ((entry = readdir(dir)))
	{
		if (!(file = new_file(path, entry))
			|| (flist->insert && flist->insert(flist->dirinfo, file)))
		{
			ls_file_del(&file);
			continue ;
		}
		if (flist->reject && flist->reject(file))
			ls_file_del(&file);
		else
			ft_dlst_pushr(&(flist->files), &(file->node));
	}
}

t_file			*ls_flist_next(t_flist *flist)
{
	t_dlist_node	*node;
	t_file			*file;
	DIR				*dir;

	if ((flist->reverse && !(node = ft_dlst_popr(&(flist->dirs))))
		|| (!(flist->reverse) && !(node = ft_dlst_popl(&(flist->dirs)))))
		return (NULL);
	file = FT_DLST_ENTRY(&(flist->dirs), node);
	if (flist->init)
		flist->init(flist->dirinfo);
	if (!(dir = opendir(file->path)))
	{
		ls_file_del(&file);
		return (ls_flist_next(flist));
	}
	list_files(file->path, dir, flist);
	closedir(dir);
	if (flist->compare)
		ft_dlst_sort(&(flist->files), (t_dlist_compare)flist->compare);
	return (file);
}
