/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:22:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 21:38:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include "ft_strings.h"

static int	print_file(t_file *file, t_flist *flist)
{
	if (flist->print && flist->print(flist->dirinfo, file))
		flist->error(file->name);
	if (!(flist->recur) || ls_file_ltype(file) || file->ltype != LS_FTYP_DIR
		|| !ft_strcmp(file->name, ".") || !ft_strcmp(file->name, ".."))
	{
		ft_dlst_remove(&(file->node));
		ls_file_del(&file);
	}
	return (1);
}

void		ls_flist_print(t_flist *flist)
{
	if (flist->recur)
	{
		ft_dlst_foreachr(&(flist->files), flist,
							(t_dlist_iterator)(&print_file));
		if (!ft_dlst_empty(&(flist->files)))
			ft_dlst_joinr(&(flist->dirs), &(flist->files));
	}
	else
	{
		ft_dlst_foreachl(&(flist->files), flist,
							(t_dlist_iterator)(&print_file));
		if (!ft_dlst_empty(&(flist->files)))
			ft_dlst_joinl(&(flist->dirs), &(flist->files));
	}
	ft_dlst_init(&(flist->files), flist->files.offset);
}
