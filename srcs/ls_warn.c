/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_warn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:43:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 12:44:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"

void	ls_warn(const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ls_vwarn(format, args);
	va_end(args);
}
