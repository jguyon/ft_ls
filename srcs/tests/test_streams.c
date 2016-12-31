/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_streams.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 23:48:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/31 12:42:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_ls.h"

TLS_TEST(test_stream_stdout)
{
	tls_stmrst();
	TLS_ASSERT(ls_printf_out("Hello, %u!", 42) == 10);
	TLS_ASSERT(tls_outcmp("Hello, 42!"));
	tls_stmrst();
	TLS_ASSERT(ls_puts_out("Hello, world!"));
	TLS_ASSERT(tls_outcmp("Hello, world!"));
	tls_stmrst();
	TLS_ASSERT(ls_putc_out('\n'));
	TLS_ASSERT(tls_outcmp("\n"));
	tls_stmrst();
	TLS_ASSERT(ls_padl_out("hello", ' ', 8));
	TLS_ASSERT(ls_padl_out("hello", ' ', 4));
	TLS_ASSERT(tls_outcmp("   hellohell"));
	tls_stmrst();
	TLS_ASSERT(ls_padr_out("hello", ' ', 8));
	TLS_ASSERT(ls_padr_out("hello", ' ', 4));
	TLS_ASSERT(tls_outcmp("hello   hell"));
}

TLS_TEST(test_stream_stderr_nonum)
{
	tls_stmrst();
	TLS_ASSERT(g_ls_status == 0);
	TLS_ASSERT(ls_printf_err(0, "Hello, %u!", 42) == 18);
	TLS_ASSERT(tls_errcmp("ft_ls: Hello, 42!\n"));
	TLS_ASSERT(g_ls_status == 1);
}

TLS_TEST(test_stream_stderr_errnum)
{
	tls_stmrst();
	TLS_ASSERT(ls_printf_err(EACCES, "Hello, %u!", 42) == 37);
	TLS_ASSERT(tls_errcmp("ft_ls: Hello, 42!: Permission denied\n"));
}

TLS_TEST(test_stream_progname)
{
	char	*name;

	name = g_ls_progname;
	TLS_ASSERT(name);
	TLS_ASSERT(name && strcmp(name, "ft_ls") == 0);
	ls_set_progname("./my_ls");
	TLS_ASSERT(g_ls_progname && strcmp(g_ls_progname, "my_ls") == 0);
	ls_set_progname("/some/deep/dir/my_ls");
	TLS_ASSERT(g_ls_progname && strcmp(g_ls_progname, "my_ls") == 0);
	g_ls_progname = name;
}

void	test_streams(void)
{
	TLS_RUN(test_stream_stdout);
	TLS_RUN(test_stream_stderr_nonum);
	TLS_RUN(test_stream_stderr_errnum);
	TLS_RUN(test_stream_progname);
}
