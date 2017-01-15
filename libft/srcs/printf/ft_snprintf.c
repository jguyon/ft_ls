/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 16:01:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 16:02:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = ft_vsnprintf(str, size, format, args);
	va_end(args);
	return (res);
}
