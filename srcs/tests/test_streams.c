/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_streams.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 23:48:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 00:29:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_ls.h"

TLS_TEST(test_stream_stdout)
{
	tls_stmrst();
	TLS_ASSERT(ls_printf_out("Hello, %u!", 42) == 10);
	TLS_ASSERT(tls_outcmp("Hello, 42!"));
}

TLS_TEST(test_stream_stderr_nonum)
{
	tls_stmrst();
	TLS_ASSERT(ls_printf_err(0, "Hello, %u!", 42) == 18);
	TLS_ASSERT(tls_errcmp("ft_ls: Hello, 42!\n"));
}

TLS_TEST(test_stream_stderr_errnum)
{
	tls_stmrst();
	TLS_ASSERT(ls_printf_err(EACCES, "Hello, %u!", 42) == 37);
	TLS_ASSERT(tls_errcmp("ft_ls: Hello, 42!: Permission denied\n"));
}

void	test_streams(void)
{
	TLS_RUN(test_stream_stdout);
	TLS_RUN(test_stream_stderr_nonum);
	TLS_RUN(test_stream_stderr_errnum);
}
