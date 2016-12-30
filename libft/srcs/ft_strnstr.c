/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:07:33 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 20:31:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define	CTOW(c)			(c * LOW_BITS)
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

static char	*next_char(const char *str, char c, size_t n)
{
	uint64_t	word;

	while (MISALIGNED(str) || n <= 8)
	{
		if (*str == c && n)
			return ((char *)str);
		if (!(*str) || !n)
			return (NULL);
		--n;
		++str;
	}
	word = CTOW(c);
	while (n > 8 && !HASZERO(*WORDS(str) & (*WORDS(str) ^ word)))
	{
		n -= 8;
		str += 8;
	}
	while (n && *str)
	{
		if (*str == c)
			return ((char *)str);
		++str;
		--n;
	}
	return (NULL);
}

char		*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	len;
	char	*next;

	if ((len = ft_strlen(little)) == 0)
		return ((char *)big);
	while (*big && (next = next_char(big, *little, n))
		   && (n = n - (next - big)) >= len)
	{
		if (ft_strncmp(next, little, len) == 0)
			return (next);
		big = next + 1;
	}
	return (NULL);
}
