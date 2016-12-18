/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:38:34 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/07 17:52:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	i;
	size_t	j;

	if (!(*little))
		return ((char *)big);
	i = 0;
	while (big[i])
	{
		j = 0;
		while (little[j] && little[j] == big[i + j])
			++j;
		if (little[j] == '\0')
			return ((char *)(big + i));
		++i;
	}
	return (NULL);
}
