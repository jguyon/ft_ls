/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:22:59 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 21:34:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MISALIGNED(s)	((uintptr_t)(s) & 7)
#define WORDS(s)		((uint64_t *)(s))
#define LOW_BITS		0x0101010101010101
#define HIGH_BITS		0x8080808080808080
#define HASZERO(w)		(((w) - LOW_BITS) & ~(w) & HIGH_BITS)

void	ft_strclr(char *str)
{
	if (!str)
		return ;
	while (MISALIGNED(str))
	{
		if (!(*str))
			return ;
		*(str++) = 0;
	}
	while (!HASZERO(*WORDS(str)))
	{
		*WORDS(str) = 0;
		str += 8;
	}
	while (*str)
		*(str++) = 0;
}
