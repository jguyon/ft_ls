/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_suffix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 19:05:22 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 19:38:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_streams.h"

int		(*g_print_suffix)(t_file *file) = NULL;

int		ls_suffix_type(t_file *file)
{
	char	c;

	if (ls_file_lstat(file) || ls_file_ltype(file))
		return (-1);
	if (file->ltype == LS_FTYP_DIR)
		c = '/';
	else if (file->ltype == LS_FTYP_LNK)
		c = '@';
	else if (file->ltype == LS_FTYP_SOCK)
		c = '=';
	else if (file->ltype == LS_FTYP_WHT)
		c = '%';
	else if (file->ltype == LS_FTYP_FIFO)
		c = '|';
	else if (file->ltype == LS_FTYP_REG && (file->lstat->st_mode & S_IEXEC))
		c = '*';
	else
		return (0);
	ft_fputc(c, FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (1);
}

int		ls_suffix_dir(t_file *file)
{
	if (ls_file_ltype(file))
		return (-1);
	if (file->ltype != LS_FTYP_DIR)
		return (0);
	ft_fputc('/', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (1);
}
