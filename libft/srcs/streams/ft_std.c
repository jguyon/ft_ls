/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_std.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 18:10:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 20:06:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_streams.h"

static size_t			stdwrite(void *fd, const char *buff, size_t size)
{
	ssize_t	count;

	if ((count = write(*((int *)fd), buff, size)) < 0)
		return (0);
	return (count);
}

static int				g_stdout_fd = 1;
static int				g_stderr_fd = 2;

t_stream				g_ft_stdout = {
	.funs = {
		.write = &stdwrite
	},
	.cookie = &g_stdout_fd,
	.size = 512
};

t_stream				g_ft_stderr = {
	.funs = {
		.write = &stdwrite
	},
	.cookie = &g_stderr_fd,
	.size = 0
};
