/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:13:06 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 12:21:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_strings.h"

char	*ft_strchr(const char *str, int c)
{
	t_mem_word	word;

	c = (char)c;
	while (FT_MEM_ALIGN(str))
	{
		if (*str == c)
			return ((char *)str);
		if (!(*str))
			return (NULL);
		++str;
	}
	word = FT_MEM_WORD(c);
	while (!FT_MEM_HASZERO(*((t_mem_word *)str)
							& (*((t_mem_word *)str) ^ word)))
		str += FT_MEM_WORDLEN;
	while (*str != c)
	{
		if (!(*str))
			return (NULL);
		++str;
	}
	return ((char *)str);
}
