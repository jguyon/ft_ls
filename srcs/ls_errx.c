/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_errx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:06:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 13:06:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"

void	ls_errx(int status, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ls_vwarnx(format, args);
	va_end(args);
	ls_exit(status);
}
