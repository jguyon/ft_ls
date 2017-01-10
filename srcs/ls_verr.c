/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_verr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:59:41 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 13:01:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"

void	ls_verr(int status, const char *format, va_list args)
{
	ls_vwarn(format, args);
	ls_exit(status);
}
