/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_tty_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:57:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 15:45:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_tty.h"
#include <sys/ioctl.h>
#include <errno.h>

size_t	ls_tty_width(void)
{
	static size_t	width = 0;
	struct winsize	win;
	int				errnum;

	errnum = errno;
	if (!width)
	{
		if (ioctl(LS_TTY_FD, TIOCGWINSZ, &win) == -1)
		{
			width = LS_TTY_DEFAULT_WIDTH;
			errno = errnum;
		}
		else
			width = win.ws_col;
	}
	return (width);
}
