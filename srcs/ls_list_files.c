/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:13:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 19:44:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <dirent.h>

static const char	*join_path(const char *path, size_t plen,
								const char *name, size_t nlen)
{
	size_t		len;
	char		*full;

	len = path[plen - 1] == '/' ? plen + nlen : plen + 1 + nlen;
	if (!(full = ft_strnew(len)))
		return (NULL);
	ft_memcpy(full, path, plen);
	if (path[plen - 1] != '/')
		full[plen++] = '/';
	ft_memcpy(full + plen, name, len - plen);
	return (full);
}

static int			is_dir(const char *path,
							struct dirent *dentry, struct stat *st)
{
	if (st->st_mode != 0)
		return (S_ISDIR(st->st_mode));
	if (dentry->d_type == DT_DIR)
		return (1);
	if (dentry->d_type != DT_UNKNOWN || lstat(path, st))
		return (0);
	return (S_ISDIR(st->st_mode));
}

static t_file		*create_file(t_flags flags,
									const char *dname, size_t dnamlen,
									struct dirent *dentry)
{
	t_file	*file;

	if (!(flags.all) && dentry->d_name[0] == '.')
		return (NULL);
	if (!(file = (t_file *)ft_memalloc(sizeof(*file)))
		|| !(file->path = join_path(dname, dnamlen,
									dentry->d_name, ft_strlen(dentry->d_name)))
		|| ((flags.mtim || flags.lfmt) && lstat(file->path, &(file->stat))))
	{
		ls_warn("%s", dentry->d_name);
		ft_memdel((void **)file->path);
		ft_memdel((void **)file);
		return (NULL);
	}
	file->name = file->path + dnamlen;
	file->is_dir = is_dir(file->path, dentry, &(file->stat));
	if (file->name[0] == '/')
		++(file->name);
	return (file);
}

void				ls_list_files(t_flags flags, t_file *dir, t_dlist *files)
{
	DIR				*dstream;
	struct dirent	*dentry;
	t_file			*file;
	const char		*dname;
	size_t			dnamlen;

	FT_DLST_INIT(files, t_file, node);
	dname = dir->path ? dir->path : dir->name;
	dnamlen = ft_strlen(dname);
	if (!(dstream = opendir(dname)))
	{
		ls_warn("%s", dir->name);
		return ;
	}
	while ((dentry = readdir(dstream)))
	{
		if ((file = create_file(flags, dname, dnamlen, dentry)))
			ft_dlst_pushr(files, &(file->node));
	}
	closedir(dstream);
	return ;
}
