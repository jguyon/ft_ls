/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:43:04 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/29 00:35:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

char	*ft_strncat(char *restrict dst, const char *restrict src, size_t len)
{
	char	*start;
	char	*mid;

	start = dst;
	dst += ft_strlen(dst);
	mid = dst;
	while (MISALIGNED(src) && (size_t)(dst - mid) < len && *src)
		*(dst++) = *(src++);
	if (*src)
	{
		while ((size_t)(dst - mid + 8) <= len && !HASZERO(*WORDS(src)))
		{
			*WORDS(dst) = *WORDS(src);
			src += 8;
			dst += 8;
		}
		while ((size_t)(dst - mid) < len && *src)
			*(dst++) = *(src++);
	}
	*dst = '\0';
	return (start);
}
