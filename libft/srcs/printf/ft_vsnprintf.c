/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 16:02:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 16:45:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_memory.h"

static size_t	str_write(void *strp, const char *buff, size_t count)
{
	char	**range;

	if (!strp)
		return (count);
	range = (char **)strp;
	if ((size_t)(range[1] - range[0]) > count)
	{
		ft_memcpy(range[0], buff, count);
		range[0] += count;
	}
	else if (range[1] < range[0])
	{
		ft_memcpy(range[0], buff, range[1] - range[0]);
		range[0] = range[1];
	}
	return (count);
}

static t_stream	g_stream = {
	.funs = {
		.write = &str_write
	},
	.size = 0
};

int				ft_vsnprintf(char *str, size_t size,
								const char *format, va_list args)
{
	char	*range[2];
	int		res;

	if (size > 0 && !str)
		return (-1);
	if (str)
	{
		range[0] = str;
		range[1] = str + size;
		g_stream.cookie = range;
	}
	else
		g_stream.cookie = NULL;
	res = ft_vfprintf(&g_stream, format, args);
	if (res < 0)
	{
		ft_clearerr(&g_stream);
		return (-1);
	}
	if (str)
		str[(size_t)res > size ? size : (size_t)res] = '\0';
	return (res);
}
