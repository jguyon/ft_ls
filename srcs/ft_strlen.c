/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:32:40 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 16:58:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

size_t	ft_strlen(const char *str)
{
	const char	*end;

	end = str;
	while (MISALIGNED(end))
	{
		if (!(*end))
			return (end - str);
		++end;
	}
	while (!HASZERO(*WORDS(end)))
		end += 8;
	while (*end)
		++end;
	return (end - str);
}
