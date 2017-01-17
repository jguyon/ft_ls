/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:39:23 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 15:41:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

#ifndef FT_MEM_OPT

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	while (n--)
		*((unsigned char *)dst++) = *((unsigned char *)src++);
	return (ret);
}

#else

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	if (FT_MEM_ALIGN(dst) == FT_MEM_ALIGN(src))
	{
		while (FT_MEM_ALIGN(dst) && n)
		{
			*((unsigned char *)dst++) = *((unsigned char *)src++);
			--n;
		}
		while (n >= FT_MEM_WORDLEN)
		{
			*((t_mem_word *)dst) = *((t_mem_word *)src);
			dst += FT_MEM_WORDLEN;
			src += FT_MEM_WORDLEN;
			n -= FT_MEM_WORDLEN;
		}
	}
	while (n--)
		*((unsigned char *)dst++) = *((unsigned char *)src++);
	return (ret);
}

#endif
