/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:22:38 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 18:36:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

int		ft_strcmp(const char *s1, const char *s2)
{
	if (MISALIGNED(s1) == MISALIGNED(s1))
	{
		while (MISALIGNED(s1))
		{
			if (!(*s1) || *s1 != *s2)
				return (*s1 - *s2);
			++s1;
			++s2;
		}
		while (!HASZERO(*WORDS(s1)) && *WORDS(s1) == *WORDS(s2))
		{
			s1 += 8;
			s2 += 8;
		}
	}
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
