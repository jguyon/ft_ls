/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:56:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 13:23:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_streams.h"

static int	print_file(t_file *file, void *acc)
{
	(void)acc;
	if (g_print_name(file) || (g_print_suffix && g_print_suffix(file) < 0))
	{
		ls_file_error(file->name);
		return (1);
	}
	ft_fputc('\n', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		ls_file_error(file->name);
	return (1);
}

void		ls_print_line(void *dirinfo, t_dlist *files)
{
	(void)dirinfo;
	ft_dlst_foreachl(files, NULL, (t_dlist_iterator)(&print_file));
}
