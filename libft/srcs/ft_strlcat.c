/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:54:36 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 17:15:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	char	*start;

	start = dst;
	dst += ft_strnlen(dst, size);
	while (MISALIGNED(src) && *src && (size_t)(dst - start) < (size - 1))
		*(dst++) = *(src++);
	if (*src)
	{
		while (!HASZERO(*WORDS(src)) && (size_t)(dst - start + 8) <= (size - 1))
		{
			*WORDS(dst) = *WORDS(src);
			src += 8;
			dst += 8;
		}
		while (*src && (size_t)(dst - start) < (size - 1))
			*(dst++) = *(src++);
	}
	if ((size_t)(dst - start) < size)
		*dst = '\0';
	return (ft_strlen(src) + (size_t)(dst - start));
}
