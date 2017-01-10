/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 21:08:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 21:29:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ft_ls.h"
#include "ls_program.h"

TLS_TEST(test_ls_parse_flags)
{
	t_flags		flags;
	int			argc = 5;
	char		*argv[5] = {"ft_ls", "-aR", "-ltr", "file", "dir"};

	g_ls_optind = 1;
	TLS_ASSERT(ls_parse_flags(argc, argv, &flags));
	TLS_ASSERT(flags.all == 1);
	TLS_ASSERT(flags.lfmt == 1);
	TLS_ASSERT(flags.mtim == 1);
	TLS_ASSERT(flags.rev == 1);
	TLS_ASSERT(flags.rec == 1);
	argc = 2;
	g_ls_optind = 1;
	TLS_ASSERT(ls_parse_flags(argc, argv, &flags));
	TLS_ASSERT(flags.all == 1);
	TLS_ASSERT(flags.lfmt == 0);
	TLS_ASSERT(flags.mtim == 0);
	TLS_ASSERT(flags.rev == 0);
	TLS_ASSERT(flags.rec == 1);
	g_ls_optind = 1;
	argv[1] = "-z";
	TLS_ASSERT(!ls_parse_flags(argc, argv, &flags));
	TLS_ASSERT(!tls_errcmp(""));
}

void	test_ls(void)
{
	TLS_RUN(test_ls_parse_flags);
}
