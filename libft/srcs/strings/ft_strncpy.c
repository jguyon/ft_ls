/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:52:18 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:03:13 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*start;

	start = dst;
	while (FT_MEM_ALIGN(src) && (size_t)(dst - start) < len && *src)
		*(dst++) = *(src++);
	if (*src)
	{
		while ((size_t)(dst - start + 8) <= len
				&& !FT_MEM_HASZERO(*((t_mem_word *)src)))
		{
			*((t_mem_word *)dst) = *((t_mem_word *)src);
			src += FT_MEM_WORDLEN;
			dst += FT_MEM_WORDLEN;
		}
		while ((size_t)(dst - start) < len && (*(dst++) = *(src++)))
			;
	}
	while ((size_t)(dst - start + FT_MEM_WORDLEN) <= len)
	{
		*((t_mem_word *)dst) = 0;
		dst += FT_MEM_WORDLEN;
	}
	while ((size_t)(dst - start) < len)
		*(dst++) = '\0';
	return (start);
}
