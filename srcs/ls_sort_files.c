/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:51:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 12:35:01 by jguyon           ###   ########.fr       */
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

static int	atimcmp(void *f1, void *f2)
{
	if (((t_file *)f1)->stat.st_atime > ((t_file *)f2)->stat.st_atime)
		return (-1);
	if (((t_file *)f1)->stat.st_atime < ((t_file *)f2)->stat.st_atime)
		return (1);
	if (LS_ATIM_NSEC(((t_file *)f1)->stat) > LS_ATIM_NSEC(((t_file *)f2)->stat))
		return (-1);
	if (LS_ATIM_NSEC(((t_file *)f1)->stat) < LS_ATIM_NSEC(((t_file *)f2)->stat))
		return (1);
	return (lexicmp(f1, f2));
}

void		ls_sort_files(t_flags flags, t_dlist *files)
{
	if (flags.sorting == LS_SORT_LEXI)
		ft_dlst_sort(files, &lexicmp);
	else if (flags.sorting == LS_SORT_TIME && flags.time == LS_TIME_MODIF)
		ft_dlst_sort(files, &mtimcmp);
	else if (flags.sorting == LS_SORT_TIME && flags.time == LS_TIME_ACCESS)
		ft_dlst_sort(files, &atimcmp);
}
