/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:13:06 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/07 17:45:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	cc;

	cc = (char)c;
	while (*str)
	{
		if (*str == cc)
			return ((char *)str);
		++str;
	}
	if (*str == cc)
		return ((char *)str);
	return (NULL);
}
