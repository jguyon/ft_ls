/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:34:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 21:29:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

#ifndef FT_MEM_OPT

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (--n && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}

#else

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (FT_MEM_ALIGN(s1) == FT_MEM_ALIGN(s2))
	{
		while (FT_MEM_ALIGN(s1))
		{
			if (!n || !(*s1) || *s1 != *s2)
				return (n ? *(unsigned char *)s1 - *(unsigned char *)s2 : 0);
			++s1;
			++s2;
			--n;
		}
		while (n > FT_MEM_WORDLEN && !FT_MEM_HASZERO(*((t_mem_word *)s1)))
		{
			if (*((t_mem_word *)s1) ^ *((t_mem_word *)s2))
				break ;
			s1 += FT_MEM_WORDLEN;
			s2 += FT_MEM_WORDLEN;
			n -= FT_MEM_WORDLEN;
		}
	}
	while (--n && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}

#endif
