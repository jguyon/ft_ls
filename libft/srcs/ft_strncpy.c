/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:52:18 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 23:02:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*start;

	start = dst;
	while (MISALIGNED(src) && (size_t)(dst - start) < len && *src)
		*(dst++) = *(src++);
	if (*src)
	{
		while ((size_t)(dst - start + 8) <= len && !HASZERO(*WORDS(src)))
		{
			*WORDS(dst) = *WORDS(src);
			src += 8;
			dst += 8;
		}
		while ((size_t)(dst - start) < len && (*(dst++) = *(src++)))
			;
	}
	while ((size_t)(dst - start + 8) <= len)
	{
		*WORDS(dst) = 0;
		dst += 8;
	}
	while ((size_t)(dst - start) < len)
		*(dst++) = '\0';
	return (start);
}
