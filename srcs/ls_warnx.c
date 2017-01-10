/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_warnx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:40:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 12:41:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"

void	ls_warnx(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ls_vwarnx(format, args);
	va_end(args);
}
