/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_open_streams.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 21:48:47 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 22:15:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static size_t			std_write(void *fd, const char *buff, size_t size)
{
	return (write(*((int *)fd), buff, size));
}

static t_stream_type	g_std_stream = {
	&std_write,
	NULL
};

int						ls_open_streams(void)
{
	if (g_ls_stdout || g_ls_stderr
		|| !(g_ls_stdout = ft_fopencookie(&g_ls_stdout_fd, g_std_stream))
		|| !(g_ls_stderr = ft_fopencookie(&g_ls_stderr_fd, g_std_stream)))
	{
		ls_close_streams();
		return (0);
	}
	return (1);
}
