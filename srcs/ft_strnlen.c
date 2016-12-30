/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 16:17:56 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 16:23:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

size_t	ft_strnlen(const char *str, size_t max)
{
	const char	*end;

	end = str;
	while (MISALIGNED(str) && (size_t)(end - str) < max)
	{
		if (!(*end))
			return (end - str);
		++end;
	}
	while (!HASZERO(*(WORDS(end))) && (size_t)(end - str + 8) <= max)
		end += 8;
	while (*end && (size_t)(end - str) < max)
		++end;
	return (end - str);
}
