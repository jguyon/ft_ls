/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 18:13:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LOW_BITS	0x0101010101010101
#define HIGH_BITS	0x8080808080808080
#define HASZERO(w)	(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 8 && *((uint64_t *)s1) == *((uint64_t *)s2))
	{
		s1 = ((uint64_t *)s1) + 1;
		s2 = ((uint64_t *)s2) + 1;
		n -= 8;
	}
	while (n)
	{
		if (*((unsigned char *)s1) != *((unsigned char *)s2))
			return ((int)(*((unsigned char *)s1) - *((unsigned char *)s2)));
		s1 = ((unsigned char *)s1) + 1;
		s2 = ((unsigned char *)s2) + 1;
		--n;
	}
	return (0);
}
