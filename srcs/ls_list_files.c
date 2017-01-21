/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:13:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 16:19:00 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

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
	struct stat	lst;

	if (st)
		return (S_ISDIR(st->st_mode));
	if (dentry->d_type == DT_DIR)
		return (1);
	if (dentry->d_type != DT_UNKNOWN || lstat(path, &lst))
		return (0);
	return (S_ISDIR(lst.st_mode));
}

static t_file		*create_file(t_flags flags,
									const char *dname, size_t dnamlen,
									struct dirent *dentry)
{
	t_file		*file;
	const char	*path;

	if (!(flags.all) && dentry->d_name[0] == '.')
		return (NULL);
	errno = 0;
	path = NULL;
	file = NULL;
	if (!(path = join_path(dname, dnamlen,
							dentry->d_name, ft_strlen(dentry->d_name)))
		|| !(file = ls_file_new(flags, path + dnamlen, path, 0)))
	{
		g_ls_status = LS_EXIT_FAILURE;
		ls_warn("%s", dentry->d_name);
		ft_memdel((void **)&(path));
		ft_memdel((void **)&(file));
		return (NULL);
	}
	file->is_dir = is_dir(file->path, dentry, file->stat);
	if (file->name[0] == '/')
		++(file->name);
	return (file);
}

void				ls_list_files(t_flags flags, t_file *dir,
									t_dinfo *dinfo, t_dlist *files)
{
	DIR				*dstream;
	struct dirent	*dentry;
	t_file			*file;
	const char		*dname;
	size_t			dnamlen;

	FT_DLST_INIT(files, t_file, node);
	ft_bzero(dinfo, sizeof(*dinfo));
	dname = dir->path ? dir->path : dir->name;
	dnamlen = ft_strlen(dname);
	errno = 0;
	if (!(dstream = opendir(dname)))
	{
		g_ls_status = LS_EXIT_FAILURE;
		ls_warn("%s", dir->name);
		return ;
	}
	while ((dentry = readdir(dstream)))
	{
		if ((file = create_file(flags, dname, dnamlen, dentry)))
			ft_dlst_pushr(files, &(file->node));
		if (file && flags.format == LS_FORMAT_LONG)
			ls_update_dinfo(dinfo, file->info);
	}
	closedir(dstream);
}
