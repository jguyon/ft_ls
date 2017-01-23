/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:53:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 19:24:15 by jguyon           ###   ########.fr       */
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

static void	print_long(t_file *file, t_print_info *info)
{
	ls_print_long(file->name, file->path, info->acc, file->info);
}

static void	print_stream(t_file *file, t_print_info *info)
{
	t_dlist_node	*next;

	next = info->flags.reverse
		? ft_dlst_prev(info->list, &(file->node))
		: ft_dlst_next(info->list, &(file->node));
	*((size_t *)info->acc) = ls_print_stream(
		file->name,
		*((size_t *)info->acc),
		next ? 0 : 1,
		ls_tty_width());
}

static void	print_columns(t_file *file, t_print_info *info)
{
	t_dlist_node	*next;

	next = info->flags.reverse
		? ft_dlst_prev(info->list, &(file->node))
		: ft_dlst_next(info->list, &(file->node));
	*((size_t *)info->acc) = ls_print_columns(
		file->name,
		*((size_t *)info->acc),
		info->dinfo->colwidth,
		next ? 0 : 1);
}

static int	print_file(void *file, void *info)
{
	if (((t_print_info *)info)->flags.format == LS_FORMAT_LONG)
		print_long(file, info);
	else if (((t_print_info *)info)->flags.format == LS_FORMAT_STREAM)
		print_stream(file, info);
	else if (((t_print_info *)info)->flags.format == LS_FORMAT_ACROSS)
		print_columns(file, info);
	else
		ls_print_line(((t_file *)file)->name);
	if (!(((t_print_info *)info)->flags.recur) || !(((t_file *)file)->is_dir)
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
	t_print_info	info;
	size_t			cols;

	info.flags = flags;
	info.list = files;
	info.acc = NULL;
	info.dinfo = dinfo;
	cols = 0;
	if (flags.format == LS_FORMAT_STREAM || flags.format == LS_FORMAT_ACROSS)
		info.acc = &cols;
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
