/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:51:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > FT_MEM_WORDLEN && *((t_mem_word *)s1) == *((t_mem_word *)s2))
	{
		s1 += FT_MEM_WORDLEN;
		s2 += FT_MEM_WORDLEN;
		n -= FT_MEM_WORDLEN;
	}
	while (n)
	{
		if (*((unsigned char *)s1) != *((unsigned char *)s2))
			return ((int)(*((unsigned char *)s1) - *((unsigned char *)s2)));
		++s1;
		++s2;
		--n;
	}
	return (0);
}
