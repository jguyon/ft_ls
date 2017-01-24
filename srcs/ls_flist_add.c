/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:58:44 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 18:08:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include "ft_memory.h"
#include "ft_strings.h"

void	ls_flist_add(t_flist *flist, const char *path, int nofollow)
{
	t_file	*file;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
		return ;
	if (!(file->path = ft_strdup(path))
		|| (nofollow && ls_file_ltype(file))
		|| (!nofollow && ls_file_type(file)))
	{
		ls_file_del(&file);
		return ;
	}
	file->name = file->path;
	if ((nofollow && file->ltype == LS_FTYP_DIR)
		|| (!nofollow && file->type == LS_FTYP_DIR))
		ft_dlst_pushr(&(flist->dirs), &(file->node));
	else
	{
		if (flist->insert && flist->insert(flist->dirinfo, file))
			ls_file_del(&file);
		else
			ft_dlst_pushr(&(flist->files), &(file->node));
	}
}
