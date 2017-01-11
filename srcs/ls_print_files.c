/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 12:53:54 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 15:48:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"
#include <sys/stat.h>
#include <stdlib.h>

static int	print_file(void *file, void *flags)
{
	ft_fprintf(FT_STDOUT, "%s\n", ((t_file *)file)->name);
	if (!(((t_flags *)flags)->rec) || !S_ISDIR(((t_file *)file)->stat.st_mode))
	{
		ft_dlst_remove(&((t_file *)file)->node);
		free((void *)((t_file *)file)->path);
		free(file);
	}
	return (1);
}

void		ls_print_files(t_flags flags, t_dlist *files)
{
	if (flags.rev)
		ft_dlst_foreachr(files, &flags, &print_file);
	else
		ft_dlst_foreachl(files, &flags, &print_file);
}
