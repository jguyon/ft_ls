/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:39:23 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:51:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	void	*ret;

	ret = dst;
	while (n >= FT_MEM_WORDLEN)
	{
		*((t_mem_word *)dst) = *((t_mem_word *)src);
		dst += FT_MEM_WORDLEN;
		src += FT_MEM_WORDLEN;
		n -= FT_MEM_WORDLEN;
	}
	while (n)
	{
		*((unsigned char *)dst) = *((unsigned char *)src);
		++dst;
		++src;
		--n;
	}
	return (ret);
}
