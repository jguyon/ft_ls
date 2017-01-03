/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:55:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 21:19:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft/ft_printf.h"

static size_t			fd_write(void *cookie, const char *buff, size_t count)
{
	return (write(*((int *)cookie), buff, count));
}

static t_stream_type	g_fd_type = {
	FT_BUFF_SIZE,
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
