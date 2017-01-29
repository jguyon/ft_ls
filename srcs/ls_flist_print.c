/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 17:22:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 13:05:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include "ft_strings.h"

static int	keep_or_del(t_file *file, t_flist *flist)
{
	if (!(flist->recur)
		|| !ft_strcmp(file->name, ".") || !ft_strcmp(file->name, "..")
		|| ls_file_ltype(file) || file->ltype != LS_FTYP_DIR)
	{
		ft_dlst_remove(&(file->node));
		ls_file_del(&file);
	}
	return (1);
}

int			ls_flist_print(t_flist *flist)
{
	int		had_files;

	had_files = ft_dlst_empty(&(flist->files)) ? 0 : 1;
	flist->print(flist->dirinfo, &(flist->files));
	ft_dlst_foreachl(&(flist->files), flist, (t_dlist_iterator)(&keep_or_del));
	if (!ft_dlst_empty(&(flist->files)))
		ft_dlst_joinl(&(flist->dirs), &(flist->files));
	ft_dlst_init(&(flist->files), flist->files.offset);
	return (had_files);
}
