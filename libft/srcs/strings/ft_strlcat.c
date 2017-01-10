/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:54:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:02:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*start;

	start = dst;
	dst += ft_strnlen(dst, size);
	while (FT_MEM_ALIGN(src) && *src && (size_t)(dst - start) < (size - 1))
		*(dst++) = *(src++);
	if (*src)
	{
		while (!FT_MEM_HASZERO(*((t_mem_word *)src))
				&& (size_t)(dst - start + FT_MEM_WORDLEN) <= (size - 1))
		{
			*((t_mem_word *)dst) = *((t_mem_word *)src);
			src += FT_MEM_WORDLEN;
			dst += FT_MEM_WORDLEN;
		}
		while (*src && (size_t)(dst - start) < (size - 1))
			*(dst++) = *(src++);
	}
	if ((size_t)(dst - start) < size)
		*dst = '\0';
	return (ft_strlen(src) + (size_t)(dst - start));
}
