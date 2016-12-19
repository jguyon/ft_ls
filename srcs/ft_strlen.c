/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:32:40 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/19 14:48:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define FT_LOMAGIC 0x0101010101010101L
#define FT_HIMAGIC 0x8080808080808080L

size_t	ft_strlen(const char *str)
{
	const char			*start;
	unsigned long int	*words;
	const char			*last;

	start = str;
	while ((ptrdiff_t)start & 7)
	{
		if (!(*start))
			return (start - str);
		++start;
	}
	words = (unsigned long int *)start;
	while (((*words - FT_LOMAGIC) & FT_HIMAGIC) == 0)
		++words;
	last = (const char *)words;
	while (*last)
		++last;
	return (last - str);
}
