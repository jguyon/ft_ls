/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_callbacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:12:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 14:27:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_callbacks.h"

TLS_TEST(test_reject_hidden)
{
	t_file	file;

	bzero(&file, sizeof(file));
	file.name = ".";
	TLS_ASSERT(ls_reject_hidden(&file));
	file.name = "..";
	TLS_ASSERT(ls_reject_hidden(&file));
	file.name = ".hidden";
	TLS_ASSERT(ls_reject_hidden(&file));
	file.name = "visible";
	TLS_ASSERT(!ls_reject_hidden(&file));
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
	TLS_ASSERT(ls_compare_mtim(&f1, &f2) < 0);
	st1.st_mtime = 1;
	st2.st_mtime = 2;
	TLS_ASSERT(ls_compare_mtim(&f1, &f2) > 0);
	st1.st_mtime = 2;
	TLS_ASSERT(ls_compare_lexi(&f1, &f2) > 0);
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

void	test_callbacks(void)
{
	TLS_RUN(test_reject_hidden);
	TLS_RUN(test_compare);
	TLS_RUN(test_print_line);
}
