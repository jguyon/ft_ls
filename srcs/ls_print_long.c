/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:59:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 15:40:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include "ls_program.h"
#include <errno.h>

void	ls_print_long(const char *name, const char *path,
							t_dinfo *info, t_finfo *finfo)
{
	errno = 0;
	path = path ? path : name;
	ls_print_mode(finfo->stat->st_mode, finfo->extended);
	ls_print_nlink(finfo->stat->st_nlink, info->max_nlink);
	ls_print_pwd(finfo, info->max_owner, info->max_group);
	if (S_ISBLK(finfo->stat->st_mode) || S_ISCHR(finfo->stat->st_mode))
		ls_print_dev(finfo->stat->st_rdev, info->max_size,
						info->max_maj, info->max_min);
	else
		ls_print_size(finfo->stat->st_size, info->max_size,
						info->max_maj, info->max_min);
	ls_print_time(finfo->time);
	ft_fprintf(FT_STDOUT, " %s", name);
	if (S_ISLNK(finfo->stat->st_mode))
		ls_print_target(finfo->target);
	ft_fputc('\n', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		ls_err(LS_EXIT_FAILURE, "stdout");
	else if (errno)
		ls_warn("%s", name);
}
