/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:51:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 17:12:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_strings.h"

static int	lexicmp(void *f1, void *f2)
{
	return (ft_strcmp(((t_file *)f1)->name, ((t_file *)f2)->name));
}

static int	timecmp(void *f1, void *f2)
{
	if (((t_file *)f1)->time->tv_sec > ((t_file *)f2)->time->tv_sec)
		return (-1);
	if (((t_file *)f1)->time->tv_sec < ((t_file *)f2)->time->tv_sec)
		return (1);
	if (((t_file *)f1)->time->tv_nsec > ((t_file *)f2)->time->tv_nsec)
		return (-1);
	if (((t_file *)f1)->time->tv_nsec < ((t_file *)f2)->time->tv_nsec)
		return (1);
	return (lexicmp(f1, f2));
}

static int	sizecmp(void *f1, void *f2)
{
	if (((t_file *)f1)->stat->st_size > ((t_file *)f2)->stat->st_size)
		return (-1);
	if (((t_file *)f1)->stat->st_size < ((t_file *)f2)->stat->st_size)
		return (1);
	return (lexicmp(f1, f2));
}

void		ls_sort_files(t_flags flags, t_dlist *files)
{
	if (flags.sorting == LS_SORT_LEXI)
		ft_dlst_sort(files, &lexicmp);
	else if (flags.sorting == LS_SORT_TIME)
		ft_dlst_sort(files, &timecmp);
	else if (flags.sorting == LS_SORT_SIZE)
		ft_dlst_sort(files, &sizecmp);
}
