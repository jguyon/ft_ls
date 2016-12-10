/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:50:47 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/07 17:30:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src,
					int c, size_t n)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*udst;
	unsigned char	*usrc;

	uc = (unsigned char)c;
	udst = (unsigned char *)dst;
	usrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		if ((udst[i] = usrc[i]) == uc)
			return (udst + i + 1);
		++i;
	}
	return (NULL);
}
