/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_long.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:59:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 23:52:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include "ft_memory.h"
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

static char	get_type(mode_t mode)
{
	if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISDIR(mode))
		return ('b');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else
		return ('-');
}

static void	put_mode(char *str, mode_t mode, char special)
{
	ft_memcpy(str, "---", 4);
	if (mode & 4)
		str[0] = 'r';
	if (mode & 2)
		str[1] = 'w';
	if ((mode & 1) && special)
		str[2] = special;
	else if (special)
		str[2] = special + ('A' - 'a');
	else if (mode & 1)
		str[2] = 'x';
}

static char	*get_date(time_t time)
{
	return (ctime(&time) + 4);
}

static void	get_target(char *buff, const char *path, size_t size)
{
	ssize_t	res;

	res = readlink(path, buff, size);
	if (res < 0 || res >= (ssize_t)size)
		buff[0] = '\0';
	else
		buff[res] = '\0';
}

int			ls_print_long(const char *name, t_dinfo *info, struct stat *st)
{
	char		mode[10];
	const char	*owner;
	const char	*group;
	int			size;
	char		target[PATH_MAX + 1];

	put_mode(mode, st->st_mode >> 6, st->st_mode & S_ISUID ? 's' : 0);
	put_mode(mode + 3, st->st_mode >> 3, st->st_mode & S_ISGID ? 's' : 0);
	put_mode(mode + 6, st->st_mode, st->st_mode & S_ISVTX ? 't' : 0);
	owner = ls_get_owner(st->st_uid);
	group = ls_get_group(st->st_gid);
	size = !S_ISBLK(st->st_mode) && !S_ISCHR(st->st_mode);
	if (S_ISLNK(st->st_mode))
		target[0] = '\0';
	else
		get_target(target, name, sizeof(target));
	return (ft_fprintf(FT_STDOUT,
		"%c%s %*zu %*.*s%*.*u %*.*s%*.*u %*.*zu%*.*lu%s%*.*lu %.12s %s%s%s\n",
		get_type(st->st_mode), mode,
		(int)info->max_nlink, st->st_nlink,
		owner ? (int)info->max_owner : 0, owner ? -1 : 0, owner ? owner : "",
		owner ? 0 : (int)info->max_owner, owner ? 0 : -1, owner ? 0 : st->st_uid,
		group ? (int)info->max_group : 0, group ? -1 : 0, group ? group : "",
		group ? 0 : (int)info->max_group, group ? 0 : -1, group ? 0 : st->st_gid,
		size ? (int)info->max_size : 0, size ? -1 : 0, size ? st->st_size : 0,
		size ? 0 : (int)info->max_maj, size ? 0 : -1, size ? 0 : LS_MAJOR(st->st_dev),
		size ? "" : ", ",
		size ? 0 : (int)info->max_min, size ? 0 : -1, size ? 0 : LS_MINOR(st->st_dev),
		get_date(st->st_mtime),
		name, *target ? " -> " : "", *target ? target : ""));
}
