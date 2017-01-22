/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_finfo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 16:46:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/22 07:35:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"

void	ls_set_finfo(t_finfo *info, const char *path,
						time_t time, struct stat *st)
{
	info->extended = ls_extended_chr(path, st->st_mode);
	info->time = time;
	info->stat = st;
	info->owner = info->no_owner || info->numeric
		? NULL : ls_get_owner(st->st_uid);
	info->group = info->no_group || info->numeric
		? NULL : ls_get_group(st->st_gid);
}
