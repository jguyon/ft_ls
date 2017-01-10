/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 22:20:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:57:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_chars.h"
#include "ft_simpleio.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char	utf[2];
	unsigned char	uc;

	uc = (unsigned char)c;
	if (!ft_isascii(uc))
	{
		utf[0] = 0xC0 | (uc >> 6);
		utf[1] = 0x80 | (0x3F & uc);
		write(fd, utf, 2);
	}
	else
		write(fd, &uc, 1);
}
