/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:08:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/13 18:08:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_memory.h"

void	put_type(char *str, struct stat *st)
{
	if (S_ISDIR(st->st_mode))
		*str = 'd';
	else if (S_ISCHR(st->st_mode))
		*str = 'c';
	else if (S_ISBLK(st->st_mode))
		*str = 'b';
	else if (S_ISFIFO(st->st_mode))
		*str = 'p';
	else if (S_ISLNK(st->st_mode))
		*str = 'l';
	else if (S_ISSOCK(st->st_mode))
		*str = 's';
}

void	put_own(char *str, struct stat *st)
{
	if (st->st_mode & S_IRUSR)
		*str = 'r';
	++str;
	if (st->st_mode & S_IWUSR)
		*str = 'w';
	++str;
	if ((st->st_mode & S_ISUID) && (st->st_mode & S_IXUSR))
		*str = 's';
	else if (st->st_mode & S_ISUID)
		*str = 'S';
	else if (st->st_mode & S_IXUSR)
		*str = 'x';
}

void	put_grp(char *str, struct stat *st)
{
	if (st->st_mode & S_IRGRP)
		*str = 'r';
	++str;
	if (st->st_mode & S_IWGRP)
		*str = 'w';
	++str;
	if ((st->st_mode & S_ISGID) && (st->st_mode & S_IXGRP))
		*str = 's';
	else if (st->st_mode & S_ISGID)
		*str = 'S';
	else if (st->st_mode & S_IXGRP)
		*str = 'x';
}

void	put_oth(char *str, struct stat *st)
{
	if (st->st_mode & S_IROTH)
		*str = 'r';
	++str;
	if (st->st_mode & S_IWOTH)
		*str = 'w';
	++str;
	if ((st->st_mode & S_ISVTX) && (st->st_mode & S_IXOTH))
		*str = 't';
	else if (st->st_mode & S_ISVTX)
		*str = 'T';
	else if (st->st_mode & S_IXOTH)
		*str = 'x';
}

void	ls_set_mode(t_finfo *info, struct stat *st)
{
	ft_memset(info->mode, '-', sizeof(info->mode) - 1);
	info->mode[sizeof(info->mode) - 1] = '\0';
	put_type(info->mode, st);
	put_own(&(info->mode[1]), st);
	put_grp(&(info->mode[4]), st);
	put_oth(&(info->mode[7]), st);
}
