/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:59:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 20:35:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_streams.h"
#include "ls_program.h"
#include <errno.h>

int		ls_print_long(const char *name, const char *path,
							t_dinfo *info, struct stat *st)
{
	errno = 0;
	ls_print_mode(st->st_mode);
	ls_print_nlink(st->st_nlink, info->max_nlink);
	ls_print_pwd(st->st_uid, info->max_owner, st->st_gid, info->max_group);
	if (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode))
		ls_print_dev(st->st_rdev, info->max_size, info->max_maj, info->max_min);
	else
		ls_print_blocks(st->st_size, info->max_size,
						info->max_maj, info->max_min);
	ls_print_time(st->st_mtime);
	ft_fputc(' ', FT_STDOUT);
	ft_fputs(name, FT_STDOUT);
	if (S_ISLNK(st->st_mode))
		ls_print_target(path, st->st_size);
	ft_fputc('\n', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		ls_err(LS_EXIT_FAILURE, "stdout");
	if (errno)
	{
		ls_warn("%s", name);
		return (-1);
	}
	return (0);
}
