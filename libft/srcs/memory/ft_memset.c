/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:57:32 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:51:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

void	*ft_memset(void *str, int c, size_t n)
{
	t_mem_word	word;
	void		*ret;

	ret = str;
	c = (unsigned char)c;
	if (n >= FT_MEM_WORDLEN)
	{
		word = FT_MEM_WORD(c);
		while (n >= FT_MEM_WORDLEN)
		{
			*((t_mem_word *)str) = word;
			str += FT_MEM_WORDLEN;
			n -= FT_MEM_WORDLEN;
		}
	}
	while (n)
	{
		*((unsigned char *)str) = c;
		++str;
		--n;
	}
	return (ret);
}
