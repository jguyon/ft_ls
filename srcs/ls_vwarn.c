/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_vwarn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:33:53 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 11:55:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_streams.h"
#include "ft_printf.h"
#include <string.h>
#include <errno.h>

void	ls_vwarn(const char *format, va_list args)
{
	const char	*prog;
	char		*errmsg;

	prog = ls_getprogname();
	ft_fflush(FT_STDOUT);
	errmsg = strerror(errno);
	ft_fprintf(FT_STDERR, "%s: ", prog);
	if (format)
	{
		ft_vfprintf(FT_STDERR, format, args);
		ft_fputs(": ", FT_STDERR);
	}
	ft_fputs(errmsg, FT_STDERR);
	ft_fputc('\n', FT_STDERR);
}
