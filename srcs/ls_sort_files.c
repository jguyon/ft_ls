/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:51:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 12:55:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_strings.h"

static int	lexicmp(void *f1, void *f2)
{
	return (ft_strcmp(((t_file *)f1)->name, ((t_file *)f2)->name));
}

static int	mtimcmp(void *f1, void *f2)
{
	if (((t_file *)f1)->stat.st_mtime > ((t_file *)f2)->stat.st_mtime)
		return (-1);
	if (((t_file *)f1)->stat.st_mtime < ((t_file *)f2)->stat.st_mtime)
		return (1);
	if (LS_MTIM_NSEC(((t_file *)f1)->stat) > LS_MTIM_NSEC(((t_file *)f2)->stat))
		return (-1);
	if (LS_MTIM_NSEC(((t_file *)f1)->stat) < LS_MTIM_NSEC(((t_file *)f2)->stat))
		return (1);
	return (lexicmp(f1, f2));
}

void		ls_sort_files(t_flags flags, t_dlist *files)
{
	if (flags.mtim)
		ft_dlst_sort(files, &mtimcmp);
	else
		ft_dlst_sort(files, &lexicmp);
}
