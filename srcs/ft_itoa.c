/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:58:22 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/05 21:34:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	m;
	size_t			i;

	m = n < 0 ? -n : n;
	i = n < 0 ? 1 : 0;
	while (m /= 10)
		++i;
	if (!(str = ft_strnew(i + 1)))
		return (NULL);
	m = n < 0 ? -n : n;
	while (m)
	{
		str[i] = m % 10 + '0';
		m /= 10;
		--i;
	}
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	return (str);
}
