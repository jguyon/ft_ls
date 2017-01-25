/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_compare_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:55:59 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 13:59:19 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"

int		ls_compare_mtim(t_file *f1, t_file *f2)
{
	if (f1->lstat->st_mtime > f2->lstat->st_mtime)
		return (-1);
	if (f1->lstat->st_mtime < f2->lstat->st_mtime)
		return (1);
	if (LS_MNSEC(f1->lstat) > LS_MNSEC(f2->lstat))
		return (-1);
	if (LS_MNSEC(f1->lstat) < LS_MNSEC(f2->lstat))
		return (1);
	return (ls_compare_lexi(f1, f2));
}

int		ls_compare_ctim(t_file *f1, t_file *f2)
{
	if (f1->lstat->st_ctime > f2->lstat->st_ctime)
		return (-1);
	if (f1->lstat->st_ctime < f2->lstat->st_ctime)
		return (1);
	if (LS_CNSEC(f1->lstat) > LS_CNSEC(f2->lstat))
		return (-1);
	if (LS_CNSEC(f1->lstat) < LS_CNSEC(f2->lstat))
		return (1);
	return (ls_compare_lexi(f1, f2));
}

int		ls_compare_atim(t_file *f1, t_file *f2)
{
	if (f1->lstat->st_atime > f2->lstat->st_atime)
		return (-1);
	if (f1->lstat->st_atime < f2->lstat->st_atime)
		return (1);
	if (LS_ANSEC(f1->lstat) > LS_ANSEC(f2->lstat))
		return (-1);
	if (LS_ANSEC(f1->lstat) < LS_ANSEC(f2->lstat))
		return (1);
	return (ls_compare_lexi(f1, f2));
}
