/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:53:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 14:20:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_format.h"
#include "ls_program.h"
#include "ls_tty.h"
#include "ft_printf.h"
#include "ft_strings.h"
#include <sys/stat.h>
#include <stdlib.h>

static int	print_file(void *file, void *info)
{
	int		err;
	int		is_last;

	err = 0;
	if (((t_proginfo *)info)->flags.format == LS_FORMAT_LONG)
		err = ls_print_long(((t_file *)file)->name, ((t_file *)file)->path,
							((t_proginfo *)info)->dinfo,
							((t_file *)file)->info);
	else if (((t_proginfo *)info)->flags.format == LS_FORMAT_STREAM)
	{
		if (((t_proginfo *)info)->flags.reverse)
			is_last = ft_dlst_prev(((t_proginfo *)info)->list,
									&((t_file *)file)->node) ? 0 : 1;
		else
			is_last = ft_dlst_next(((t_proginfo *)info)->list,
								   &((t_file *)file)->node) ? 0 : 1;
		*((size_t *)((t_proginfo *)info)->dinfo) =
			ls_print_stream(((t_file *)file)->name,
				*((size_t *)((t_proginfo *)info)->dinfo),
				is_last,
				ls_tty_width());
	}
	else
		ls_print_line(((t_file *)file)->name);
	if (err)
		g_ls_status = LS_EXIT_FAILURE;
	if (!(((t_proginfo *)info)->flags.recur) || !(((t_file *)file)->is_dir)
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
	size_t		cols;

	info.flags = flags;
	info.list = files;
	cols = 0;
	if (flags.format == LS_FORMAT_STREAM)
		info.dinfo = &cols;
	else
		info.dinfo = dinfo;
	if (flags.reverse)
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
