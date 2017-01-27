/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:12:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 13:09:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_callbacks.h"
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

TLS_TEST(test_reject_hidden)
{
	TLS_ASSERT(ls_reject_hidden("."));
	TLS_ASSERT(ls_reject_implied("."));
	TLS_ASSERT(ls_reject_hidden(".."));
	TLS_ASSERT(ls_reject_implied(".."));
	TLS_ASSERT(ls_reject_hidden(".hidden"));
	TLS_ASSERT(!ls_reject_implied(".hidden"));
	TLS_ASSERT(ls_reject_hidden("..hidden"));
	TLS_ASSERT(!ls_reject_implied("..hidden"));
	TLS_ASSERT(!ls_reject_hidden("visible"));
	TLS_ASSERT(!ls_reject_implied("visible"));
}

TLS_TEST(test_compare)
{
	t_file		f1;
	struct stat	st1;
	t_file		f2;
	struct stat	st2;

	bzero(&f1, sizeof(f1));
	bzero(&f2, sizeof(f2));
	bzero(&st1, sizeof(st1));
	bzero(&st2, sizeof(st2));
	f1.lstat = &st1;
	f2.lstat = &st2;
	f1.name = "abc";
	f2.name = "abd";
	TLS_ASSERT(ls_compare_lexi(&f1, &f2) < 0);
	f2.name = "abc";
	TLS_ASSERT(ls_compare_lexi(&f1, &f2) == 0);
	f2.name = "abb";
	TLS_ASSERT(ls_compare_lexi(&f1, &f2) > 0);
	st1.st_mtime = 2;
	st2.st_mtime = 1;
	TLS_ASSERT(ls_compare_time(&f1, &f2) < 0);
	st1.st_mtime = 1;
	st2.st_mtime = 2;
	TLS_ASSERT(ls_compare_time(&f1, &f2) > 0);
	st1.st_mtime = 2;
	TLS_ASSERT(ls_compare_time(&f1, &f2) > 0);
	st1.st_size = 2;
	st2.st_size = 1;
	TLS_ASSERT(ls_compare_size(&f1, &f2) < 0);
	st1.st_size = 1;
	st2.st_size = 2;
	TLS_ASSERT(ls_compare_size(&f1, &f2) > 0);
	st1.st_size = 2;
	TLS_ASSERT(ls_compare_size(&f1, &f2) > 0);
}

TLS_TEST(test_print_line)
{
	t_file	file;

	bzero(&file, sizeof(file));
	file.name = "filename";
	TLS_ASSERT(!ls_print_line(NULL, &file));
	TLS_ASSERT(tls_outcmp("filename\n"));
}

TLS_TEST(test_print_long)
{
	t_long_dinfo	dinfo;
	t_file			*file;
	char			*str;
	struct stat		st;
	struct passwd	*pw;
	struct group	*gr;

	file = calloc(1, sizeof(*file));
	ls_init_long(&dinfo);
	TLS_INIT_FS;
	TLS_TOUCHT("197001010000", "file1");
	TLS_CHMOD("777", "file1");
	file->name = "file1";
	file->path = strdup(TLS_DIR "file1");
	TLS_ASSERT(!ls_insert_long(&dinfo, file));
	TLS_ASSERT(dinfo.has_files == 1);
	TLS_ASSERT(dinfo.total == 0);
	TLS_ASSERT(dinfo.max_nlink == 1);
	lstat(TLS_DIR "file1", &st);
	pw = getpwuid(st.st_uid);
	gr = getgrgid(st.st_gid);
	TLS_ASSERT(dinfo.max_owner == strlen(pw->pw_name));
	TLS_ASSERT(dinfo.max_group == strlen(gr->gr_name));
	TLS_ASSERT(dinfo.max_size == 1);
	TLS_ASSERT(!ls_print_long(&dinfo, file));
	asprintf(&str, "-rwxrwxrwx  1 %s  %s  0 Jan  1  1970 file1\n",
			 pw->pw_name,
			 gr->gr_name);
	TLS_ASSERT(tls_outcmp(str));
	free(str);
	ls_file_del(&file);
	TLS_STOP_FS;
}

void	test_callbacks(void)
{
	TLS_RUN(test_reject_hidden);
	TLS_RUN(test_compare);
	TLS_RUN(test_print_line);
	TLS_RUN(test_print_long);
}
