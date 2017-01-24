/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 21:44:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 21:50:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"

int		del_file(t_file *file, void *acc)
{
	(void)acc;
	ft_dlst_remove(&(file->node));
	ls_file_del(&file);
	return (1);
}

void	ls_flist_clear(t_flist *flist)
{
	ft_dlst_foreachl(&(flist->files), NULL, (t_dlist_iterator)(&del_file));
	ft_dlst_foreachl(&(flist->dirs), NULL, (t_dlist_iterator)(&del_file));
}
