/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:57:32 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 18:37:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define LOW_BITS	0x0101010101010101

void	*ft_memset(void *str, int c, size_t n)
{
	uint64_t	word;
	void		*ret;

	ret = str;
	if (n >= 8)
	{
		word = LOW_BITS * (unsigned char)c;
		while (n >= 8)
		{
			*((uint64_t *)str) = word;
			str = ((uint64_t *)str) + 1;
			n -= 8;
		}
	}
	while (n)
	{
		*((unsigned char *)str) = c;
		str = ((unsigned char *)str) + 1;
		--n;
	}
	return (ret);
}
