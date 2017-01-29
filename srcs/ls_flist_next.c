/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_next.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:31:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 14:18:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <errno.h>

static t_file	*new_file(const char *path, struct dirent *entry)
{
	t_file	*file;
	size_t	dlen;
	size_t	flen;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
		return (NULL);
	file->ltype = entry->d_type;
	dlen = ft_strlen(path);
	if (path[dlen - 1] == '/')
		--dlen;
	flen = ft_strlen(entry->d_name);
	if ((file->path = ft_strnew(dlen + flen + 1)))
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

static void		list_files(const char *name, const char *path,
							DIR *dir, t_flist *flist)
{
	struct dirent	*entry;
	t_file			*file;

	errno = 0;
	while ((entry = readdir(dir)))
	{
		if (flist->reject && flist->reject(entry->d_name))
			continue ;
		if (!(file = new_file(path, entry)))
		{
			flist->error(entry->d_name);
			ls_file_del(&file);
		}
		else if (flist->insert && flist->insert(flist->dirinfo, file))
		{
			flist->error(entry->d_name);
			ls_file_del(&file);
		}
		else
			ft_dlst_pushr(&(flist->files), &(file->node));
	}
	if (errno)
		flist->error(name);
}

static void		reverse_files(t_dlist *files)
{
	t_dlist			new;
	t_dlist_node	*curr;

	ft_dlst_init(&new, files->offset);
	while ((curr = ft_dlst_popl(files)))
		ft_dlst_pushl(&new, curr);
	if (!ft_dlst_empty(&new))
		ft_dlst_joinl(files, &new);
}

t_file			*ls_flist_next(t_flist *flist,
								int (*print)(void *dirinfo, t_file *file))
{
	t_dlist_node	*node;
	t_file			*file;
	DIR				*dir;

	if (!(node = ft_dlst_popl(&(flist->dirs))))
		return (NULL);
	file = FT_DLST_ENTRY(&(flist->dirs), node);
	if (flist->init)
		flist->init(flist->dirinfo);
	if ((print && print(flist->dirinfo, file)) || !(dir = opendir(file->path)))
	{
		flist->error(file->name);
		return (file);
	}
	list_files(file->name, file->path, dir, flist);
	closedir(dir);
	if (flist->compare)
		ft_dlst_sort(&(flist->files), (t_dlist_compare)flist->compare);
	if (flist->reverse)
		reverse_files(&(flist->files));
	return (file);
}
