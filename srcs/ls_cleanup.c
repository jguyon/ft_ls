/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:06:57 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 14:52:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_streams.h"

int		ls_cleanup(int status)
{
	size_t	i;

	i = 0;
	while (i < LS_ATEXIT_SIZE)
	{
		if (g_ls_atexit[i])
			g_ls_atexit[i]();
		++i;
	}
	return (status);
}
