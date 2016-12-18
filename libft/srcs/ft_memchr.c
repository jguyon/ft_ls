/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:53:37 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/07 17:36:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*ustr;

	uc = (unsigned char)c;
	ustr = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (ustr[i] == uc)
			return (ustr + i);
		++i;
	}
	return (NULL);
}
