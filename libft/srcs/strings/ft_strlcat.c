/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:54:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 21:11:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

#ifndef FT_MEM_OPT

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*start;

	start = dst;
	dst += ft_strnlen(dst, size);
	while (*src && (size_t)(dst - start) < (size - 1))
		*(dst++) = *(src++);
	if ((size_t)(dst - start) < size)
		*dst = '\0';
	return (ft_strlen(src) + (size_t)(dst - start));
}

#else

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*start;

	start = dst;
	dst += ft_strnlen(dst, size);
	if (FT_MEM_ALIGN(src) == FT_MEM_ALIGN(dst))
	{
		while (FT_MEM_ALIGN(src) && *src && (size_t)(dst - start + 1) < size)
			*(dst++) = *(src++);
		if (*src)
		{
			while (!FT_MEM_HASZERO(*((t_mem_word *)src))
					&& (size_t)(dst - start + FT_MEM_WORDLEN + 1) <= size)
			{
				*((t_mem_word *)dst) = *((t_mem_word *)src);
				src += FT_MEM_WORDLEN;
				dst += FT_MEM_WORDLEN;
			}
		}
	}
	while (*src && (size_t)(dst - start + 1) < size)
		*(dst++) = *(src++);
	if ((size_t)(dst - start) < size)
		*dst = '\0';
	return (ft_strlen(src) + (size_t)(dst - start));
}

#endif
