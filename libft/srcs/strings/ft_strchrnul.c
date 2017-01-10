/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrnul.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:40:29 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:00:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

char	*ft_strchrnul(const char *str, int c)
{
	t_mem_word	word;

	c = (char)c;
	while (FT_MEM_ALIGN(str))
	{
		if (!(*str) || *str == c)
			return ((char *)str);
		++str;
	}
	word = FT_MEM_WORD(c);
	while (!FT_MEM_HASZERO(*((t_mem_word *)str)
							& (*((t_mem_word *)str) ^ word)))
		str += FT_MEM_WORDLEN;
	while (*str && *str != c)
		++str;
	return ((char *)str);
}
