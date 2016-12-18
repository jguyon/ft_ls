/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:24:14 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/07 17:34:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*udst;
	unsigned char	*usrc;

	if (dst > src)
	{
		udst = (unsigned char *)dst;
		usrc = (unsigned char *)src;
		i = len;
		while (i-- > 0)
			udst[i] = usrc[i];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
