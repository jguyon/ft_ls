/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 22:22:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 12:22:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_strings.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	if (FT_MEM_ALIGN(s1) == FT_MEM_ALIGN(s1))
	{
		while (FT_MEM_ALIGN(s1))
		{
			if (!(*s1) || *s1 != *s2)
				return (*s1 - *s2);
			++s1;
			++s2;
		}
		while (!FT_MEM_HASZERO(*((t_mem_word *)s1))
				&& *((t_mem_word *)s1) == *((t_mem_word *)s2))
		{
			s1 += FT_MEM_WORDLEN;
			s2 += FT_MEM_WORDLEN;
		}
	}
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
}
