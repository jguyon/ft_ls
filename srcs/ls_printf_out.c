/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printf_out.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 22:36:34 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 22:50:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_printf_out(const char *format, ...)
{
	va_list	ap;
	int		res;

	if (!g_ls_stdout)
		return (-1);
	va_start(ap, format);
	res = ft_vfprintf(g_ls_stdout, format, ap);
	va_end(ap);
	return (res);
}
