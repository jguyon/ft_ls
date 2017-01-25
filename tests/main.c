/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 15:57:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 14:15:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include "test_ls.h"
#include "ls_program.h"
#include "ls_format.h"

static char		g_outbuf[8192];
static char		g_errbuf[8192];

static size_t	buff_write(void *cookie, const char *buf, size_t count)
{
	ft_strncat(cookie, buf, count);
	return (count);
}

static void		clear_caches(void)
{
	/* ls_cache_clear(&g_ls_owners); */
	/* ls_cache_clear(&g_ls_groups); */
}

static void		close_streams(void)
{
	ft_fclose(FT_STDOUT);
	ft_fclose(FT_STDERR);
}

int			main(void)
{
	g_ft_stdout.cookie = g_outbuf;
	g_ft_stdout.funs.write = &buff_write;
	g_ft_stderr.cookie = g_errbuf;
	g_ft_stderr.funs.write = &buff_write;
	ls_atexit(&clear_caches);
	ls_atexit(&close_streams);
	TLS_START;
	test_program();
	test_cache();
	test_files();
	test_callbacks();
	/* test_ls(); */
	/* test_format(); */
	TLS_SUMUP;
	return (ls_cleanup(0));
}

int			tls_outcmp(const char *str)
{
	int		cmp;

	ft_fflush(FT_STDOUT);
	cmp = ft_strcmp(g_outbuf, str);
	/* printf("%s\n", g_outbuf); */
	ft_bzero(g_outbuf, 8192);
	return (cmp == 0);
}

int			tls_errcmp(const char *str)
{
	int		cmp;

	ft_fflush(FT_STDERR);
	cmp = ft_strcmp(g_errbuf, str);
	/* printf("%s\n", g_errbuf); */
	ft_bzero(g_errbuf, 8192);
	return (cmp == 0);
}
