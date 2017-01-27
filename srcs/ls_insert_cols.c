/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_insert_cols.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:19:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 20:34:00 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_strings.h"

int		ls_insert_cols(t_cols_dinfo *dinfo, t_file *file)
{
	size_t	width;

	if (g_need_lstat && ls_file_lstat(file))
		return (-1);
	if (dinfo)
	{
		++(dinfo->count);
		width = ft_strlen(file->name);
		if (width > dinfo->colwidth)
			dinfo->colwidth = width;
	}
	return (0);
}
