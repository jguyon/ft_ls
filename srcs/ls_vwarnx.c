/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_vwarnx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:28:28 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 11:56:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_streams.h"
#include "ft_printf.h"

void	ls_vwarnx(const char *format, va_list args)
{
	const char	*prog;

	prog = ls_getprogname();
	ft_fflush(FT_STDOUT);
	ft_fprintf(FT_STDERR, "%s: ", prog);
	if (format)
		ft_vfprintf(FT_STDERR, format, args);
	ft_fputc('\n', FT_STDERR);
}
