/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:38:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 16:38:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	*ft_strstr(const char *big, const char *little)
{
	const char	*str;
	const char	*cmp;

	if (!(*little))
		return ((char *)big);
	while (*big)
	{
		str = big;
		cmp = little;
		while (*cmp && *str == *cmp)
		{
			++str;
			++cmp;
		}
		if (!(*cmp))
			return ((char *)big);
		++big;
	}
	return (NULL);
}
