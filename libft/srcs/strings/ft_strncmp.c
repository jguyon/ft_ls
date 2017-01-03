/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:34:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 12:22:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_strings.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (FT_MEM_ALIGN(s1) == FT_MEM_ALIGN(s1))
	{
		while (FT_MEM_ALIGN(s1))
		{
			if (!n || !(*s1) || *s1 != *s2)
				return (n ? *s1 - *s2 : 0);
			++s1;
			++s2;
			--n;
		}
		while (n > 8 && !FT_MEM_HASZERO(*((t_mem_word *)s1))
				&& *((t_mem_word *)s1) == *((t_mem_word *)s2))
		{
			s1 += FT_MEM_WORDLEN;
			s2 += FT_MEM_WORDLEN;
			n -= FT_MEM_WORDLEN;
		}
	}
	while (n && *s1 && *s1 == *s2)
	{
		++s1;
		++s2;
		--n;
	}
	return (n ? *s1 - *s2 : 0);
}
