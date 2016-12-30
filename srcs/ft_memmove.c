/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:24:14 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/28 18:49:52 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*cpy_left(void *dst, const void *src, size_t n)
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

static void	*cpy_right(void *dst, const void *src, size_t n)
{
	dst += n;
	src += n;
	while (n >= 8)
	{
		dst = ((uint64_t *)dst) - 1;
		src = ((uint64_t *)src) - 1;
		*((uint64_t *)dst) = *((uint64_t *)src);
		n -= 8;
	}
	while (n)
	{
		dst = ((unsigned char *)dst) - 1;
		src = ((unsigned char *)src) - 1;
		*((unsigned char *)dst) = *((unsigned char *)src);
		--n;
	}
	return (dst);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst > src)
		return (cpy_right(dst, src, len));
	else
		return (cpy_left(dst, src, len));
}
