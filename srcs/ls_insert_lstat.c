/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_insert_lstat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:01:35 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 20:33:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"

int		g_need_lstat = 0;

int		ls_insert_lstat(void *dirinfo, t_file *file)
{
	(void)dirinfo;
	if (g_need_lstat)
		return (ls_file_lstat(file));
	return (0);
}
