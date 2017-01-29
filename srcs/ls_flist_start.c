/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:25:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 14:19:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"

static void	reverse_files(t_dlist *files)
{
	t_dlist			new;
	t_dlist_node	*curr;

	ft_dlst_init(&new, files->offset);
	while ((curr = ft_dlst_popl(files)))
		ft_dlst_pushl(&new, curr);
	if (!ft_dlst_empty(&new))
		ft_dlst_joinl(files, &new);
}

void		ls_flist_start(t_flist *flist)
{
	if (flist->compare)
	{
		ft_dlst_sort(&(flist->dirs), (t_dlist_compare)flist->compare);
		ft_dlst_sort(&(flist->files), (t_dlist_compare)flist->compare);
	}
	if (flist->reverse)
	{
		reverse_files(&(flist->dirs));
		reverse_files(&(flist->files));
	}
}
