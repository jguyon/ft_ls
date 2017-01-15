/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 15:31:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 16:35:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_memory.h"

static size_t	string_write(void *strp, const char *buff, size_t count)
{
	char	*str;

	str = *((char **)strp);
	if (!str)
		return (count);
	ft_memcpy(str, buff, count);
	return (count);
}

static t_stream	g_stream = {
	.funs = {
		.write = &string_write
	},
	.size = 0
};

int				ft_vsprintf(char *str, const char *format, va_list args)
{
	int res;

	g_stream.cookie = &str;
	res = ft_vfprintf(&g_stream, format, args);
	if (res < 0)
	{
		ft_clearerr(&g_stream);
		return (-1);
	}
	str[res] = '\0';
	return (res);
}
