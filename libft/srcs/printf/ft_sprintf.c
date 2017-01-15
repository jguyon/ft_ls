/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 15:55:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 15:57:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_sprintf(char *str, const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = ft_vsprintf(str, format, args);
	va_end(args);
	return (res);
}
