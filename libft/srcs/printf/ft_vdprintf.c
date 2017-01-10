/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:41:44 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 21:03:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

static size_t	fd_write(void *fd, const char *buff, size_t count)
{
	return (write(*((int *)fd), buff, count));
}

static t_stream	g_stream = {
	.funs = {
		.write = &fd_write
	},
	.size = 0,
};

int				ft_vdprintf(int fd, const char *format, va_list args)
{
	int		res;

	g_stream.cookie = &fd;
	res = ft_vfprintf(&g_stream, format, args);
	if (ft_fclose(&g_stream))
		return (-1);
	return (res);
}
