/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_atexit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 14:41:43 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 15:00:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include <stddef.h>
#include <errno.h>

void	(*g_ls_atexit[LS_ATEXIT_SIZE])(void);

int		ls_atexit(void (*f)(void))
{
	size_t	i;

	i = 0;
	while (i < LS_ATEXIT_SIZE && !(g_ls_atexit[i]))
		++i;
	if (i == 0)
	{
		errno = ENOMEM;
		return (-1);
	}
	g_ls_atexit[i - 1] = f;
	return (0);
}
