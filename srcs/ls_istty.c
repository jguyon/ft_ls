/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_istty.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:58:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 12:11:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_tty.h"
#include <termios.h>
#include <unistd.h>
#include <errno.h>

int		ls_istty(void)
{
	static int		istty = -1;
	struct termios	term;
	int				errnum;

	if (istty == -1)
	{
		errnum = errno;
		if (tcgetattr(LS_TTY_FD, &term))
			istty = 0;
		else
			istty = 1;
		errno = errnum;
	}
	return (istty);
}
