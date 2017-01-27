/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:58:44 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 13:39:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include "ft_memory.h"
#include "ft_strings.h"

static void	add_file(t_flist *flist, t_file *file)
{
	if (flist->insert && flist->insert(flist->dirinfo, file))
		ls_file_del(&file);
	else
		ft_dlst_pushr(&(flist->files), &(file->node));
}

static void	add_dir(t_flist *flist, t_file *file)
{
	if (flist->insert && flist->insert(NULL, file))
		ls_file_del(&file);
	else
		ft_dlst_pushr(&(flist->dirs), &(file->node));
}

void		ls_flist_add(t_flist *flist, const char *path,
							int nofollow, int nodirs)
{
	t_file	*file;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
		return ;
	if (!(file->path = ft_strdup(path))
		|| (!nodirs && ls_file_ltype(file)))
	{
		flist->error(path);
		ls_file_del(&file);
		return ;
	}
	file->name = file->path;
	if (!nodirs
		&& (file->ltype == LS_FTYP_DIR
			|| (!nofollow && file->ltype == LS_FTYP_DIR)
			|| (!nofollow && file->ltype == LS_FTYP_LNK
				&& !ls_file_type(file) && file->type == LS_FTYP_DIR)))
		add_dir(flist, file);
	else
		add_file(flist, file);
}
