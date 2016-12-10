/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 22:28:04 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/06 19:36:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	m;
	char			c;

	if (n == 0)
		return (ft_putchar_fd('0', fd));
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		m = -n;
	}
	else
		m = n;
	c = m % 10 + '0';
	m = m / 10;
	if (m)
		ft_putnbr_fd(m, fd);
	ft_putchar_fd(c, fd);
}
