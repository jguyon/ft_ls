/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:32:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 12:53:21 by jguyon           ###   ########.fr       */
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

void	test_program(void)
{
	TLS_RUN(test_program_progname);
	TLS_RUN(test_program_warn);
}
