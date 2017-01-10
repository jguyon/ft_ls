/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:32:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 16:28:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_program.h"
#include <errno.h>

TLS_TEST(test_program_progname)
{
	TLS_ASSERT(!ls_getprogname());
	ls_setprogname("simple");
	TLS_ASSERT(ls_getprogname() && strcmp(ls_getprogname(), "simple") == 0);
	ls_setprogname("multi/parts/prog");
	TLS_ASSERT(ls_getprogname() && strcmp(ls_getprogname(), "prog") == 0);
	ls_setprogname(NULL);
}

TLS_TEST(test_program_warn)
{
	ls_setprogname("ft_ls");
	errno = EPERM;
	ls_warn(NULL);
	TLS_ASSERT(tls_errcmp("ft_ls: Operation not permitted\n"));
	ls_warn("%s", "somefile");
	TLS_ASSERT(tls_errcmp("ft_ls: somefile: Operation not permitted\n"));
	ls_warnx("invalid option -- %c", 'z');
	TLS_ASSERT(tls_errcmp("ft_ls: invalid option -- z\n"));
	ls_setprogname(NULL);
}

TLS_TEST(test_program_getopt)
{
	int		ac = 5;
	char	*av[5] = {"ft_ls", "-d", "-abc", "--", "file"};

	ls_setprogname("ft_ls");
	TLS_ASSERT(ls_getopt(ac, av, "abcd") == 'd');
	TLS_ASSERT(ls_getopt(ac, av, "abcd") == 'a');
	TLS_ASSERT(ls_getopt(ac, av, "abcd") == 'b');
	TLS_ASSERT(ls_getopt(ac, av, "abcd") == 'c');
	TLS_ASSERT(ls_getopt(ac, av, "abcd") == -1);
	TLS_ASSERT(g_ls_optind == 4);
	TLS_ASSERT(tls_errcmp(""));
	g_ls_optind = 1;
	TLS_ASSERT(ls_getopt(ac, av, "bcd") == 'd');
	TLS_ASSERT(ls_getopt(ac, av, "bcd") == '?');
	TLS_ASSERT(tls_errcmp("ft_ls: illegal option -- a\n"));
	TLS_ASSERT(g_ls_optind == 3);
	ls_setprogname(NULL);
}

void	test_program(void)
{
	TLS_RUN(test_program_progname);
	TLS_RUN(test_program_warn);
	TLS_RUN(test_program_getopt);
}
