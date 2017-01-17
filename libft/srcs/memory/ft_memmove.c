/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:24:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 16:02:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

#ifndef FT_MEM_OPT

static void	*cpy_left(void *dst, const void *src, size_t n)
{
	void	*ret;

	ret = dst;
	while (n--)
		*((unsigned char *)dst++) = *((unsigned char *)src++);
	return (ret);
}

static void	*cpy_right(void *dst, const void *src, size_t n)
{
	dst += n;
	src += n;
	while (n--)
		*((unsigned char *)--dst) = *((unsigned char *)--src);
	return (dst);
}

#else

static void	*cpy_left(void *dst, const void *src, size_t n)
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

static void	*cpy_right(void *dst, const void *src, size_t n)
{
	dst += n;
	src += n;
	if (FT_MEM_ALIGN(dst) == FT_MEM_ALIGN(src))
	{
		while (FT_MEM_ALIGN(dst) && n)
		{
			*((unsigned char *)--dst) = *((unsigned char *)--src);
			--n;
		}
		while (n >= FT_MEM_WORDLEN)
		{
			dst -= FT_MEM_WORDLEN;
			src -= FT_MEM_WORDLEN;
			*((t_mem_word *)dst) = *((t_mem_word *)src);
			n -= FT_MEM_WORDLEN;
		}
	}
	while (n--)
		*((unsigned char *)--dst) = *((unsigned char *)--src);
	return (dst);
}

#endif

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst > src)
		return (cpy_right(dst, src, len));
	else
		return (cpy_left(dst, src, len));
}
