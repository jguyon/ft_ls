/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 12:22:06 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 20:10:14 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_streams.h"

int			(*g_print_name)(t_file *file) = &ls_name_normal;

int			ls_name_normal(t_file *file)
{
	ft_fputs(file->name, FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}

static void	print_color(mode_t mode)
{
	if ((mode & (S_IFDIR | S_IWOTH | S_ISVTX)) == (S_IFDIR | S_IWOTH | S_ISVTX))
		ft_fputs(LS_COLOR_OTHS, FT_STDOUT);
	else if ((mode & (S_IFDIR | S_IWOTH)) == (S_IFDIR | S_IWOTH))
		ft_fputs(LS_COLOR_OTHD, FT_STDOUT);
	else if (S_ISDIR(mode))
		ft_fputs(LS_COLOR_DIR, FT_STDOUT);
	else if (S_ISLNK(mode))
		ft_fputs(LS_COLOR_LNK, FT_STDOUT);
	else if (S_ISSOCK(mode))
		ft_fputs(LS_COLOR_SOCK, FT_STDOUT);
	else if (S_ISFIFO(mode))
		ft_fputs(LS_COLOR_FIFO, FT_STDOUT);
	else if (S_ISBLK(mode))
		ft_fputs(LS_COLOR_BLK, FT_STDOUT);
	else if (S_ISCHR(mode))
		ft_fputs(LS_COLOR_CHR, FT_STDOUT);
	else if ((mode & (S_IFREG | S_IEXEC | S_ISUID))
				== (S_IFREG | S_IEXEC | S_ISUID))
		ft_fputs(LS_COLOR_XUID, FT_STDOUT);
	else if ((mode & (S_IFREG | S_IEXEC | S_ISGID))
				== (S_IFREG | S_IEXEC | S_ISGID))
		ft_fputs(LS_COLOR_XGID, FT_STDOUT);
	else if ((mode & (S_IFREG | S_IEXEC)) == (S_IFREG | S_IEXEC))
		ft_fputs(LS_COLOR_EXEC, FT_STDOUT);
}

int			ls_name_color(t_file *file)
{
	if (ls_file_lstat(file))
		return (-1);
	print_color(file->lstat->st_mode);
	ft_fputs(file->name, FT_STDOUT);
	ft_fputs(LS_COLOR_RESET, FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}
