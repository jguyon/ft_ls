/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:59:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 13:25:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ls_long_format.h"
#include "ft_printf.h"
#include <inttypes.h>
#include <errno.h>

static void	print_pwd(t_long_dinfo *dinfo, t_file *file)
{
	const char	*str;

	if ((str = ((t_long_finfo *)file->info)->owner))
		ft_fprintf(FT_STDOUT, " %*s", -(int)dinfo->max_owner, str);
	else
		ft_fprintf(FT_STDOUT, " %*u",
			-(int)dinfo->max_owner, file->lstat->st_uid);
	ft_fputc(' ', FT_STDOUT);
	if ((str = ((t_long_finfo *)file->info)->group))
		ft_fprintf(FT_STDOUT, " %*s", -(int)dinfo->max_group, str);
	else
		ft_fprintf(FT_STDOUT, " %*u",
					-(int)dinfo->max_group, file->lstat->st_gid);
}

static void	print_dev(t_long_dinfo *dinfo, t_file *file)
{
	size_t	maj_width;
	size_t	min_width;

	maj_width = dinfo->max_min + dinfo->max_maj + 3 < dinfo->max_size
		? dinfo->max_size - dinfo->max_min - 3 : dinfo->max_maj;
	min_width = dinfo->max_min;
	ft_fprintf(FT_STDOUT, "   %*u, %*u",
		(int)maj_width, LS_MAJOR(file->lstat->st_rdev),
		(int)min_width, LS_MINOR(file->lstat->st_rdev));
}

static void	print_size(t_long_dinfo *dinfo, t_file *file)
{
	size_t	width;

	width = (dinfo->max_maj == 0 && dinfo->max_min == 0)
		|| (dinfo->max_maj + dinfo->max_min + 3) < dinfo->max_size
		? dinfo->max_size : dinfo->max_maj + dinfo->max_min + 3;
	ft_fprintf(FT_STDOUT, "  %*llu", (int)width, file->lstat->st_size);
}

static int	print_file(t_file *file, t_long_dinfo *dinfo)
{
	t_long_finfo	*finfo;

	errno = 0;
	finfo = (t_long_finfo *)file->info;
	ft_fprintf(FT_STDOUT, "%s%c %*ju", finfo->mode, finfo->extended,
		(int)dinfo->max_nlink, (uintmax_t)file->lstat->st_nlink);
	print_pwd(dinfo, file);
	if (file->ltype == LS_FTYP_BLK || file->ltype == LS_FTYP_CHR)
		print_dev(dinfo, file);
	else
		print_size(dinfo, file);
	ft_fprintf(FT_STDOUT, " %s ", finfo->time);
	if (g_print_name(file) || (g_print_suffix && g_print_suffix(file) < 0))
	{
		ls_file_error(file->name);
		return (1);
	}
	if (finfo->target[0])
		ft_fprintf(FT_STDOUT, " -> %s", finfo->target);
	ft_fputc('\n', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		ls_file_error(file->name);
	return (1);
}

void		ls_print_long(t_long_dinfo *dinfo, t_dlist *files)
{
	ft_dlst_foreachl(files, dinfo, (t_dlist_iterator)(&print_file));
}
