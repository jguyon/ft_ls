/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:40:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 15:06:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_vprintf(const char *format, va_list args)
{
	int		res;

	res = ft_vfprintf(FT_STDOUT, format, args);
	if (ft_fflush(FT_STDOUT) < 0)
	{
		ft_clearerr(FT_STDOUT);
		return (-1);
	}
	return (res);
}
