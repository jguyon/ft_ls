/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:13:06 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 17:30:14 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define	CTOW(c)			(c * LOW_BITS)
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

char	*ft_strchr(const char *str, int c)
{
	uint64_t	word;

	c = (char)c;
	while (MISALIGNED(str))
	{
		if (*str == c)
			return ((char *)str);
		if (!(*str))
			return (NULL);
		++str;
	}
	word = CTOW(c);
	while (!HASZERO(*WORDS(str) & (*WORDS(str) ^ word)))
		str += 8;
	while (*str != c)
	{
		if (!(*str))
			return (NULL);
		++str;
	}
	return ((char *)str);
}
