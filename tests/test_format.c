/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 23:56:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_format.h"
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

TLS_TEST(test_format_dinfo)
{
	t_dinfo		info;
	struct stat	st;

	bzero(&info, sizeof(info));
	st.st_mode = S_IFBLK;
	st.st_blocks = 512;
	st.st_nlink = 16;
	st.st_uid = getuid();
	st.st_gid = getgid();
	st.st_dev = makedev(13, 3);
	ls_update_info(&info, &st);
	TLS_ASSERT(info.total == 512);
	TLS_ASSERT(info.max_nlink == 2);
	TLS_ASSERT(info.max_owner == strlen(getpwuid(st.st_uid)->pw_name));
	TLS_ASSERT(info.max_group == strlen(getgrgid(st.st_gid)->gr_name));
	TLS_ASSERT(info.max_size == 0);
	TLS_ASSERT(info.max_maj == 2);
	TLS_ASSERT(info.max_min == 1);
	ls_cache_clear(&g_ls_owners);
	ls_cache_clear(&g_ls_groups);
}

TLS_TEST(test_format_print_long)
{
	t_dinfo		info;
	struct stat	st;
	char		*str;
	char		date[13];

	info.max_nlink = 2;
	info.max_owner = 20;
	info.max_group = 20;
	info.max_size = 10;
	info.max_maj = 4;
	info.max_min = 3;
	st.st_mode = S_IFBLK | S_IRWXU | S_ISUID | S_IXGRP | S_ISVTX;
	st.st_nlink = 2;
	st.st_uid = UINT_MAX;
	st.st_gid = UINT_MAX;
	st.st_size = 1024;
	st.st_dev = makedev(2, 1);
	st.st_mtime = 0;
	strftime(date, 13, "%b %e %H:%M", localtime(&st.st_mtime));
	TLS_ASSERT(ls_print_long("file", &info, &st) > 0);
	asprintf(&str, "brws--x--T  2 %20u %20u %4u, %3u %s file\n",
			 st.st_uid, st.st_gid, major(st.st_dev), minor(st.st_dev),
			 date);
	TLS_ASSERT(tls_outcmp(str));
	free(str);
}

void	test_format(void)
{
	TLS_RUN(test_format_dinfo);
	TLS_RUN(test_format_print_long);
}
