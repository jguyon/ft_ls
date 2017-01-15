/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 01:19:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_format.h"
#include <unistd.h>
#include <grp.h>

TLS_TEST(test_format_mode)
{
	t_finfo		info;
	struct stat	st;

	st.st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX;
	ls_set_mode(&info, &st);
	TLS_ASSERT(strcmp(info.mode, "drwsrwsrwt") == 0);
}

TLS_TEST(test_format_nlinks)
{
	t_finfo		info;
	struct stat	st;

	st.st_nlink = 132;
	TLS_ASSERT(ls_set_nlinks(&info, &st) == 3);
	TLS_ASSERT(strcmp(info.nlinks, "132") == 0);
}

TLS_TEST(test_format_owner)
{
	t_finfo		info;
	struct stat	st;
	char		*login;

	st.st_uid = getuid();
	login = getenv("LOGNAME");
	TLS_ASSERT(ls_set_owner(&info, &st) == strlen(login));
	TLS_ASSERT(strcmp(info.owner, login) == 0);
	info.owner = NULL;
	TLS_ASSERT(ls_set_owner(&info, &st) == strlen(login));
	TLS_ASSERT(strcmp(info.owner, login) == 0);
	st.st_uid = 2000000000;
	TLS_ASSERT(ls_set_owner(&info, &st) == 10);
	TLS_ASSERT(strcmp(info.owner, "2000000000") == 0);
}

TLS_TEST(test_format_group)
{
	t_finfo		info;
	struct stat	st;
	char		*group;

	st.st_gid = getgid();
	group = getgrgid(st.st_gid)->gr_name;
	TLS_ASSERT(ls_set_group(&info, &st) == strlen(group));
	TLS_ASSERT(strcmp(info.group, group) == 0);
	info.group = NULL;
	TLS_ASSERT(ls_set_group(&info, &st) == strlen(group));
	TLS_ASSERT(strcmp(info.group, group) == 0);
	st.st_gid = 2000000000;
	TLS_ASSERT(ls_set_group(&info, &st) == 10);
	TLS_ASSERT(strcmp(info.group, "2000000000") == 0);
}

void	test_format(void)
{
	TLS_RUN(test_format_mode);
	TLS_RUN(test_format_nlinks);
	TLS_RUN(test_format_owner);
	TLS_RUN(test_format_group);
}
