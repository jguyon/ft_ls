/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_err.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:03:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 13:05:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"

void	ls_err(int status, const char *format, ...)
{
	va_list	args;

	va_start(args, format);
	ls_vwarn(format, args);
	va_end(args);
	ls_exit(status);
}
