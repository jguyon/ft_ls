/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:50:47 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 17:06:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LOW_BITS	0x0101010101010101
#define HIGH_BITS	0x8080808080808080
#define HASZERO(w)	(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

void	*ft_memccpy(void *restrict dst, const void *restrict src,
					int c, size_t n)
{
	uint64_t	word;

	c = (unsigned char)c;
	if (n > 8)
	{
		word = LOW_BITS * c;
		while (n > 8 && !HASZERO(*((uint64_t *)src) ^ word))
		{
			*((uint64_t *)dst) = *((uint64_t *)src);
			dst = ((uint64_t *)dst) + 1;
			src = ((uint64_t *)src) + 1;
			n -= 8;
		}
	}
	while (n)
	{
		if ((*((unsigned char *)dst) = *((unsigned char *)src)) == c)
			return ((unsigned char *)dst + 1);
		dst = ((unsigned char *)dst) + 1;
		src = ((unsigned char *)src) + 1;
		--n;
	}
	return (NULL);
}
