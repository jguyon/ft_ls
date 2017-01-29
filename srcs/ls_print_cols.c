/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_cols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:34:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 14:43:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ls_tty.h"
#include "ft_printf.h"
#include "ft_strings.h"

static int			print_file(t_cols_dinfo *dinfo, t_file *file)
{
	int		has_suffix;

	has_suffix = 0;
	if (g_print_name(file)
		|| (g_print_suffix && (has_suffix = g_print_suffix(file)) < 0))
		return (-1);
	++(dinfo->x);
	if (dinfo->x == dinfo->cols
		|| (dinfo->x + 1 == dinfo->cols
			&& dinfo->y >= (dinfo->count - 1) % dinfo->rows + 1))
	{
		dinfo->x = 0;
		++(dinfo->y);
		ft_fputc('\n', FT_STDOUT);
	}
	else
		ft_fprintf(FT_STDOUT, "%*s",
				   dinfo->colwidth - ft_strlen(file->name) - has_suffix, "");
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}

static void			do_print_cols(t_cols_dinfo *dinfo, t_dlist *files)
{
	t_file			*arr[dinfo->count];
	size_t			i;
	size_t			j;
	t_dlist_node	*curr;

	curr = ft_dlst_first(files);
	i = 0;
	while (i < dinfo->count)
	{
		arr[i] = curr ? FT_DLST_ENTRY(files, curr) : NULL;
		curr = ft_dlst_next(files, curr);
		++i;
	}
	i = 0;
	while (i < dinfo->rows)
	{
		j = i;
		while (j < dinfo->count && arr[j])
		{
			if (print_file(dinfo, arr[j]))
				ls_file_error(arr[j]->name);
			j += dinfo->rows;
		}
		++i;
	}
}

void				ls_print_cols(t_cols_dinfo *dinfo, t_dlist *files)
{
	dinfo->colwidth += g_print_suffix ? 2 : 1;
	if (dinfo->count > 0)
	{
		if (ls_tty_width() > dinfo->colwidth)
			dinfo->cols = ls_tty_width() / dinfo->colwidth;
		else
			dinfo->cols = 1;
		dinfo->rows = dinfo->count / dinfo->cols
			+ !!(dinfo->count % dinfo->cols);
		while (dinfo->count / dinfo->rows
				+ !!(dinfo->count % dinfo->rows) < dinfo->cols)
		{
			--(dinfo->cols);
			dinfo->rows = dinfo->count / dinfo->cols
				+ !!(dinfo->count % dinfo->cols);
		}
		do_print_cols(dinfo, files);
	}
}
