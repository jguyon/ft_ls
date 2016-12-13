/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 15:45:41 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 18:07:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	put_mode_type(struct stat *sb, char *str)
{
	if (S_ISDIR(sb->st_mode))
		str[0] = 'd';
	else if (S_ISCHR(sb->st_mode))
		str[0] = 'c';
	else if (S_ISBLK(sb->st_mode))
		str[0] = 'b';
	else if (S_ISFIFO(sb->st_mode))
		str[0] = 'p';
	else if (S_ISLNK(sb->st_mode))
		str[0] = 'l';
	else if (S_ISSOCK(sb->st_mode))
		str[0] = 's';
	else
		str[0] = '-';
}

static void	put_own_perm(struct stat *sb, char *str)
{
	str += 1;
	ft_strncpy(str, "---", 3);
	if ((sb->st_mode & S_IRUSR) == S_IRUSR)
		str[0] = 'r';
	if ((sb->st_mode & S_IWUSR) == S_IWUSR)
		str[1] = 'w';
	if ((sb->st_mode & (S_IXUSR | S_ISUID)) == (S_IXUSR | S_ISUID))
		str[2] = 's';
	else if ((sb->st_mode & S_ISUID) == S_ISUID)
		str[2] = 'S';
	else if ((sb->st_mode & S_IXUSR) == S_IXUSR)
		str[2] = 'x';
}

static void	put_grp_perm(struct stat *sb, char *str)
{
	str += 4;
	ft_strncpy(str, "---", 3);
	if ((sb->st_mode & S_IRGRP) == S_IRGRP)
		str[0] = 'r';
	if ((sb->st_mode & S_IWGRP) == S_IWGRP)
		str[1] = 'w';
	if ((sb->st_mode & (S_IXGRP | S_ISGID)) == (S_IXGRP | S_ISGID))
		str[2] = 's';
	else if ((sb->st_mode & S_ISGID) == S_ISGID)
		str[2] = 'S';
	else if ((sb->st_mode & S_IXGRP) == S_IXGRP)
		str[2] = 'x';
}

static void	put_oth_perm(struct stat *sb, char *str)
{
	str += 7;
	ft_strncpy(str, "---", 3);
	if ((sb->st_mode & S_IROTH) == S_IROTH)
		str[0] = 'r';
	if ((sb->st_mode & S_IWOTH) == S_IWOTH)
		str[1] = 'w';
	if ((sb->st_mode & (S_IXOTH | S_ISVTX)) == (S_IXOTH | S_ISVTX))
		str[2] = 't';
	else if ((sb->st_mode & S_ISVTX) == S_ISVTX)
		str[2] = 'T';
	else if ((sb->st_mode & S_IXOTH) == S_IXOTH)
		str[2] = 'x';
}

char		*ls_file_mode(struct stat *sb)
{
	char	*str;

	if (!(str = ft_strnew(10)))
		return (NULL);
	put_mode_type(sb, str);
	put_own_perm(sb, str);
	put_grp_perm(sb, str);
	put_oth_perm(sb, str);
	return (str);
}
