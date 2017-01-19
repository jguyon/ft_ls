/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 11:13:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 15:52:42 by jguyon           ###   ########.fr       */
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
	errno = 0;
	if (!(file = (t_file *)ft_memalloc(sizeof(*file)))
		|| !(file->path = join_path(dname, dnamlen,
									dentry->d_name, ft_strlen(dentry->d_name)))
		|| ((flags.mtim || flags.lfmt) && lstat(file->path, &(file->stat))))
	{
		g_ls_status = LS_EXIT_FAILURE;
		ls_warn("%s", dentry->d_name);
		if (file)
			ft_memdel((void **)&(file->path));
		ft_memdel((void **)&(file));
		return (NULL);
	}
	file->name = file->path + dnamlen;
	file->is_dir = is_dir(file->path, dentry, &(file->stat));
	if (flags.lfmt)
	{
		file->extended = ls_extended_chr(file->path);
		file->owner = ls_get_owner(file->stat.st_uid);
		file->group = ls_get_group(file->stat.st_gid);
	}
	if (file->name[0] == '/')
		++(file->name);
	return (file);
}

static const char	*g_curr_dir = ".";

static t_file		*copy_file(t_file *other, const char *name)
{
	t_file	*file;

	if (!(file = (t_file *)malloc(sizeof(*file))))
	{
		g_ls_status = LS_EXIT_FAILURE;
		ls_warn("%s", name);
		return (NULL);
	}
	ft_memcpy(file, other, sizeof(*file));
	file->path = NULL;
	file->name = name;
	return (NULL);
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
		if (flags.all && ft_strcmp(dentry->d_name, ".") == 0)
			file = copy_file(dir, g_curr_dir);
		else
			file = create_file(flags, dname, dnamlen, dentry);
		if (file)
			ft_dlst_pushr(files, &(file->node));
		if (file && flags.lfmt)
			ls_update_info(dinfo, &(file->stat));
	}
	closedir(dstream);
}
