/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_verrx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:01:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 13:02:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"

void	ls_verrx(int status, const char *format, va_list args)
{
	ls_vwarnx(format, args);
	ls_exit(status);
}
