/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:39:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 13:52:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_callbacks.h"
#include "ft_printf.h"

static int	print_first(void *dirinfo, t_file *file)
{
	(void)dirinfo;
	ft_fprintf(FT_STDOUT, "%s:\n", file->path);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}

static int	print_dir(void *dirinfo, t_file *file)
{
	(void)dirinfo;
	ft_fprintf(FT_STDOUT, "\n%s:\n", file->path);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}

int			ls_print_files(t_flags *flags, t_flist *flist)
{
	t_file			*dir;
	int				(*print)(void *, t_file *);

	print = flags->singlearg ? NULL : &print_first;
	if (ls_flist_print(flist) && (dir = ls_flist_next(flist, &print_dir)))
	{
		if (flags->format == LS_FORMAT_LONG)
			ls_print_total(flist->dirinfo);
		ls_flist_print(flist);
		ls_file_del(&dir);
	}
	else if ((dir = ls_flist_next(flist, print)))
	{
		if (flags->format == LS_FORMAT_LONG)
			ls_print_total(flist->dirinfo);
		ls_flist_print(flist);
		ls_file_del(&dir);
	}
	while ((dir = ls_flist_next(flist, &print_dir)))
	{
		ls_flist_print(flist);
		ls_file_del(&dir);
	}
	return (g_ls_status);
}
