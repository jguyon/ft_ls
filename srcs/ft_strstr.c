/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:38:34 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 19:41:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	size_t	len;

	if ((len = ft_strlen(little)) == 0)
		return ((char *)big);
	while (*big && (big = ft_strchr(big, *little)))
	{
		if (ft_strncmp(big, little, len) == 0)
			return ((char *)big);
		++big;
	}
	return (NULL);
}
