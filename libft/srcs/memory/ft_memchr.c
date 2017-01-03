/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:53:37 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 12:20:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	t_mem_word	word;

	c = (unsigned char)c;
	if (n > FT_MEM_WORDLEN)
	{
		word = FT_MEM_WORD(c);
		while (n > FT_MEM_WORDLEN
				&& !FT_MEM_HASZERO(*((t_mem_word *)str) ^ word))
		{
			str += FT_MEM_WORDLEN;
			n -= FT_MEM_WORDLEN;
		}
	}
	while (n)
	{
		if (*((unsigned char *)str) == c)
			return ((void *)str);
		++str;
		--n;
	}
	return (NULL);
}
