/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 00:52:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_format.h"
#include <unistd.h>

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
	st.st_uid = 123;
	TLS_ASSERT(ls_set_owner(&info, &st) == 3);
	TLS_ASSERT(strcmp(info.owner, "123") == 0);
}

void	test_format(void)
{
	TLS_RUN(test_format_mode);
	TLS_RUN(test_format_nlinks);
	TLS_RUN(test_format_owner);
}
