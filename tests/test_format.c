/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 12:58:36 by jguyon           ###   ########.fr       */
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
	st.st_rdev = makedev(13, 3);
	ls_update_info(&info, &st);
	TLS_ASSERT(info.total == 512);
	TLS_ASSERT(info.has_files);
	TLS_ASSERT(info.max_nlink == 2);
	TLS_ASSERT(info.max_owner == strlen(getpwuid(st.st_uid)->pw_name));
	TLS_ASSERT(info.max_group == strlen(getgrgid(st.st_gid)->gr_name));
	TLS_ASSERT(info.max_size == 0);
	TLS_ASSERT(info.max_maj == 2);
	TLS_ASSERT(info.max_min == 1);
	ls_cache_clear(&g_ls_owners);
	ls_cache_clear(&g_ls_groups);
}

TLS_TEST(test_format_print_line)
{
	ls_print_line("file");
	TLS_ASSERT(tls_outcmp("file\n"));
}

TLS_TEST(test_format_print_total)
{
	t_dinfo	info;

	info.total = 123;
	info.has_files = 0;
	ls_print_total(&info);
	TLS_ASSERT(tls_outcmp(""));
	info.has_files = 1;
	ls_print_total(&info);
	TLS_ASSERT(tls_outcmp("total 123\n"));
}

TLS_TEST(test_format_print_long)
{
	t_dinfo		dinfo;
	t_finfo		finfo;
	struct stat	st;
	char		*str;
	char		date[13];

	finfo.extended = '@';
	finfo.stat = &st;
	dinfo.max_nlink = 2;
	dinfo.max_owner = 20;
	dinfo.max_group = 20;
	dinfo.max_size = 10;
	dinfo.max_maj = 2;
	dinfo.max_min = 3;
	st.st_mode = S_IFBLK | S_IRWXU | S_ISUID | S_IXGRP | S_ISVTX;
	st.st_nlink = 2;
	st.st_uid = UINT_MAX / 2;
	st.st_gid = UINT_MAX / 2;
	st.st_size = 1024;
	st.st_rdev = makedev(16, 127);
	st.st_mtime = 0;
	strftime(date, 13, "%b %e  %Y", localtime(&st.st_mtime));
	ls_print_long("file", "/path/to/file", &dinfo, &finfo);
	asprintf(&str, "brws--x--T@  2 %-20u  %-20u   %4u, %3u %s file\n",
			 st.st_uid, st.st_gid, major(st.st_rdev), minor(st.st_rdev),
			 date);
	TLS_ASSERT(tls_outcmp(str));
	free(str);
}

TLS_TEST(test_print_dir)
{
	ls_print_dir("somedir");
	TLS_ASSERT(tls_outcmp("somedir:\n"));
}

void	test_format(void)
{
	TLS_RUN(test_format_dinfo);
	TLS_RUN(test_format_print_line);
	TLS_RUN(test_format_print_long);
	TLS_RUN(test_format_print_total);
	TLS_RUN(test_print_dir);
}
