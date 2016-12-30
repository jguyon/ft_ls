/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:53:37 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 17:16:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LOW_BITS	0x0101010101010101
#define HIGH_BITS	0x8080808080808080
#define HASZERO(w)	(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

void	*ft_memchr(const void *str, int c, size_t n)
{
	uint64_t	word;

	c = (unsigned char)c;
	if (n > 8)
	{
		word = LOW_BITS * c;
		while (n > 8 && !HASZERO(*((uint64_t *)str) ^ word))
		{
			str = ((uint64_t *)str) + 1;
			n -= 8;
		}
	}
	while (n)
	{
		if (*((unsigned char *)str) == c)
			return ((unsigned char *)str);
		str = ((unsigned char *)str) + 1;
		--n;
	}
	return (NULL);
}
