/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:35:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 15:36:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = ft_vdprintf(fd, format, args);
	va_end(args);
	return (res);
}
