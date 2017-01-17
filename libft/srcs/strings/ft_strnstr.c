/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:07:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 16:43:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

char		*ft_strnstr(const char *big, const char *little, size_t n)
{
	const char	*str;
	const char	*cmp;
	size_t		l;

	if (!(*little))
		return ((char *)big);
	while (n && *big)
	{
		str = big;
		cmp = little;
		l = n;
		while (l && *cmp && *str == *cmp)
		{
			++str;
			++cmp;
			--l;
		}
		if (!(*cmp))
			return ((char *)big);
		--n;
		++big;
	}
	return (NULL);
}
