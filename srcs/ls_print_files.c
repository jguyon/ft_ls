/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:39:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 20:37:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_callbacks.h"
#include "ft_printf.h"

int		ls_print_files(t_flags *flags, t_flist *flist)
{
	t_file	*dir;

	dir = NULL;
	if (ls_flist_print(flist) && (dir = ls_flist_next(flist)))
		ft_fputc('\n', FT_STDOUT);
	if (dir || (dir = ls_flist_next(flist)))
	{
		if (!(flags->singlearg))
			ft_fprintf(FT_STDOUT, "%s:\n", dir->path);
		ls_flist_print(flist);
		ls_file_del(&dir);
	}
	while ((dir = ls_flist_next(flist)))
	{
		ft_fprintf(FT_STDOUT, "\n%s:\n", dir->path);
		ls_flist_print(flist);
		ls_file_del(&dir);
	}
	return (LS_EXIT_STATUS);
}
