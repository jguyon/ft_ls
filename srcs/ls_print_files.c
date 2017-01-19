/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:53:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 12:54:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_format.h"
#include "ls_program.h"
#include "ft_printf.h"
#include "ft_strings.h"
#include <sys/stat.h>
#include <stdlib.h>

static int	print_file(void *file, void *info)
{
	int		err;
	t_finfo	finfo;

	err = 0;
	finfo.extended = ((t_file *)file)->extended;
	finfo.stat = &(((t_file *)file)->stat);
	if (((t_proginfo *)info)->flags.lfmt)
		err = ls_print_long(((t_file *)file)->name, ((t_file *)file)->path,
							((t_proginfo *)info)->dinfo, &finfo);
	else
		ls_print_line(((t_file *)file)->name);
	if (err)
		g_ls_status = LS_EXIT_FAILURE;
	if (!(((t_proginfo *)info)->flags.rec) || !(((t_file *)file)->is_dir)
		|| !ft_strcmp(((t_file *)file)->name, ".")
		|| !ft_strcmp(((t_file *)file)->name, ".."))
	{
		ft_dlst_remove(&((t_file *)file)->node);
		ls_destroy_file(file);
	}
	return (1);
}

void		ls_print_files(t_flags flags, t_dlist *files, t_dinfo *dinfo,
							t_dlist *dirs)
{
	t_proginfo	info;

	info.flags = flags;
	info.dinfo = dinfo;
	if (flags.rev)
	{
		ft_dlst_foreachr(files, &info, &print_file);
		if (!ft_dlst_empty(files))
			ft_dlst_joinr(dirs, files);
	}
	else
	{
		ft_dlst_foreachl(files, &info, &print_file);
		if (!ft_dlst_empty(files))
			ft_dlst_joinl(dirs, files);
	}
	ft_dlst_init(files, files->offset);
	if (!ft_dlst_empty(dirs))
		ft_fputc('\n', FT_STDOUT);
}
