/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:39:23 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 18:45:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	void	*ret;

	ret = dst;
	while (n >= 8)
	{
		*((uint64_t *)dst) = *((uint64_t *)src);
		dst = ((uint64_t *)dst) + 1;
		src = ((uint64_t *)src) + 1;
		n -= 8;
	}
	while (n)
	{
		*((unsigned char *)dst) = *((unsigned char *)src);
		dst = ((unsigned char *)dst) + 1;
		src = ((unsigned char *)src) + 1;
		--n;
	}
	return (ret);
}
