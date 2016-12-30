/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:42:42 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 20:28:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

char	*ft_strcpy(char *dst, const char *src)
{
	char	*ret;

	ret = dst;
	while (MISALIGNED(src))
	{
		if (!(*(dst++) = *(src++)))
			return (ret);
	}
	while (!HASZERO(*WORDS(src)))
	{
		*WORDS(dst) = *WORDS(src);
		src += 8;
		dst += 8;
	}
	while ((*(dst++) = *(src++)))
		;
	return (ret);
}
