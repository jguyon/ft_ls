/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:55:28 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:03:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (res);
}
