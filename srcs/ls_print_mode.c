/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:08:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 11:30:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_memory.h"
#include "ft_streams.h"

static void	set_type(char str[1], mode_t mode)
{
	if (S_ISBLK(mode))
		str[0] = 'b';
	else if (S_ISCHR(mode))
		str[0] = 'c';
	else if (S_ISDIR(mode))
		str[0] = 'd';
	else if (S_ISFIFO(mode))
		str[0] = 'p';
	else if (S_ISLNK(mode))
		str[0] = 'l';
	else if (S_ISSOCK(mode))
		str[0] = 's';
}

static void	set_owner(char str[3], mode_t mode)
{
	if (mode & S_IRUSR)
		str[0] = 'r';
	if (mode & S_IWUSR)
		str[1] = 'w';
	if ((mode & S_ISUID) && (mode & S_IXUSR))
		str[2] = 's';
	else if (mode & S_ISUID)
		str[2] = 'S';
	else if (mode & S_IXUSR)
		str[2] = 'x';
}

static void	set_group(char str[3], mode_t mode)
{
	if (mode & S_IRGRP)
		str[0] = 'r';
	if (mode & S_IWGRP)
		str[1] = 'w';
	if ((mode & S_ISGID) && (mode & S_IXGRP))
		str[2] = 's';
	else if (mode & S_ISGID)
		str[2] = 'S';
	else if (mode & S_IXGRP)
		str[2] = 'x';
}

static void	set_other(char str[3], mode_t mode)
{
	if (mode & S_IROTH)
		str[0] = 'r';
	else if (mode & S_IWOTH)
		str[1] = 'w';
	else if ((mode & S_ISVTX) && (mode & S_IXOTH))
		str[2] = 't';
	else if (mode & S_ISVTX)
		str[2] = 'T';
	else if (mode & S_IXOTH)
		str[2] = 'x';
}

void		ls_print_mode(mode_t mode)
{
	char	str[11];

	ft_memcpy(str, "---------- ", 11);
	set_type(str, mode);
	set_owner(&(str[1]), mode);
	set_group(&(str[4]), mode);
	set_other(&(str[7]), mode);
	ft_fwrite(str, 11, FT_STDOUT);
}
