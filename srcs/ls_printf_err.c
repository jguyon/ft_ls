/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 22:56:01 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/11 00:23:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_printf_err(int errnum, const char *format, ...)
{
	va_list	ap;
	int		res;

	if (!g_ls_stderr || ft_fflush(g_ls_stdout) < 0)
		return (-1);
	va_start(ap, format);
	res = ft_fprintf(g_ls_stderr, "%s: ", g_ls_progname);
	res += ft_vfprintf(g_ls_stderr, format, ap);
	if (errnum != 0)
		res += ft_fprintf(g_ls_stderr, ": %s", strerror(errnum));
	ft_fputc('\n', g_ls_stderr);
	res += 1;
	ft_fflush(g_ls_stderr);
	va_end(ap);
	return (ft_ferror(g_ls_stderr) ? -1 : res);
}
