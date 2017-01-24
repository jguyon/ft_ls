/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_flist_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 16:25:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 16:28:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"

void	ls_flist_start(t_flist *flist)
{
	if (flist->compare)
	{
		ft_dlst_sort(&(flist->dirs), (t_dlist_compare)flist->compare);
		ft_dlst_sort(&(flist->files), (t_dlist_compare)flist->compare);
	}
}
