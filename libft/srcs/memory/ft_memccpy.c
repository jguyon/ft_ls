/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:50:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:50:50 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_mem_word	word;

	c = (unsigned char)c;
	while (FT_MEM_ALIGN(src) && n)
	{
		if ((*((unsigned char *)dst++) = *((unsigned char *)src++)) == c)
			return (dst);
		--n;
	}
	if (n > FT_MEM_WORDLEN)
		word = FT_MEM_WORD(c);
	while (n > FT_MEM_WORDLEN
			&& !FT_MEM_HASZERO(*((t_mem_word *)src) ^ word))
	{
		*((t_mem_word *)dst) = *((t_mem_word *)src);
		dst += FT_MEM_WORDLEN;
		src += FT_MEM_WORDLEN;
		n -= FT_MEM_WORDLEN;
	}
	while (n && (*((unsigned char *)dst++) = *((unsigned char *)src++)) != c)
		--n;
	return (n ? dst : NULL);
}
