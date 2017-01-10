/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 21:07:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:03:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

static char	*next_char(const char *str, char c, size_t n)
{
	t_mem_word	word;

	while (FT_MEM_ALIGN(str) || n <= FT_MEM_WORDLEN)
	{
		if (*str == c && n)
			return ((char *)str);
		if (!(*(str++)) || !(n--))
			return (NULL);
	}
	word = FT_MEM_WORD(c);
	while (n > FT_MEM_WORDLEN
			&& !FT_MEM_HASZERO(*((t_mem_word *)str)
								& (*((t_mem_word *)str) ^ word)))
	{
		n -= FT_MEM_WORDLEN;
		str += FT_MEM_WORDLEN;
	}
	while (n && *str)
	{
		if (*str == c)
			return ((char *)str);
		++str;
		--n;
	}
	return (NULL);
}

char		*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	len;
	char	*next;

	if ((len = ft_strlen(little)) == 0)
		return ((char *)big);
	while (*big && (next = next_char(big, *little, n))
			&& (n = n - (next - big)) >= len)
	{
		if (ft_strncmp(next, little, len) == 0)
			return (next);
		big = next + 1;
	}
	return (NULL);
}
