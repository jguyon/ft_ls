/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:55:55 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:02:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static size_t			fd_write(void *cookie, const char *buff, size_t count)
{
	return (write(*((int *)cookie), buff, count));
}

static t_stream_type	g_fd_type = {
	&fd_write,
	NULL
};

int						ft_vdprintf(int fd, const char *format, va_list ap)
{
	t_stream	*stream;
	int			count;

	if (!(stream = ft_fopencookie(&fd, g_fd_type)))
		return (-1);
	count = ft_vfprintf(stream, format, ap);
	if (ft_fclose(stream))
		count = -1;
	return (count);
}
