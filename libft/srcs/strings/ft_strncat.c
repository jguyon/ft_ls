/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:43:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 12:22:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_strings.h"

char	*ft_strncat(char *dst, const char *src, size_t len)
{
	char	*start;
	char	*mid;

	start = dst;
	dst += ft_strlen(dst);
	mid = dst;
	while (FT_MEM_ALIGN(src) && (size_t)(dst - mid) < len && *src)
		*(dst++) = *(src++);
	if (*src)
	{
		while ((size_t)(dst - mid + FT_MEM_WORDLEN) <= len
				&& !FT_MEM_HASZERO(*((t_mem_word *)src)))
		{
			*((t_mem_word *)dst) = *((t_mem_word *)src);
			src += FT_MEM_WORDLEN;
			dst += FT_MEM_WORDLEN;
		}
		while ((size_t)(dst - mid) < len && *src)
			*(dst++) = *(src++);
	}
	*dst = '\0';
	return (start);
}
