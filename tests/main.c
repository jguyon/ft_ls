/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 15:57:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 16:42:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"

int			main(void)
{
	g_ls_stdout_fd = -1;
	g_ls_stderr_fd = -1;
	tls_stmrst();
	TLS_START;
	test_utils();
	test_streams();
	test_parse_args();
	TLS_SUMUP;
	ls_close_streams();
	close(g_ls_stdout_fd);
	close(g_ls_stderr_fd);
	return (0);
}

static int	fdcmp(int fd, const char *str)
{
	char	*fdstr;
	size_t	size;
	size_t	i;
	int		res;

	size = strlen(str);
	if (!(fdstr = (char *)malloc(size + 2)))
		return (0);
	lseek(fd, 0, SEEK_SET);
	i = 0;
	while (i <= size && read(fd, fdstr + i, 1) == 1)
		++i;
	fdstr[i] = '\0';
	res = (strcmp(fdstr, str) == 0);
	free(fdstr);
	return (res);
}

static void	fdrst(int *fd, const char *filename)
{
	if (*fd >= 0)
		close(*fd);
	*fd = open(filename, O_CREAT | O_TRUNC | O_RDWR);
	fchmod(*fd, S_IRUSR | S_IWUSR);
}

void		tls_stmrst(void)
{
	ls_close_streams();
	fdrst(&g_ls_stdout_fd, "/tmp/test_ls_out");
	fdrst(&g_ls_stderr_fd, "/tmp/test_ls_err");
	ls_open_streams();
}

int			tls_outcmp(const char *str)
{
	ft_fflush(g_ls_stdout);
	return (fdcmp(g_ls_stdout_fd, str));
}

int			tls_errcmp(const char *str)
{
	ft_fflush(g_ls_stderr);
	return (fdcmp(g_ls_stderr_fd, str));
}
