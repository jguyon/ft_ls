/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:26:26 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 16:16:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

#ifndef FT_MEM_OPT

char	*ft_strrchr(const char *str, int c)
{
	char	*res;

	c = (char)c;
	res = NULL;
	while (1)
	{
		if (*str == c)
			res = (char *)str;
		if (!(*str))
			return (res);
		++str;
	}
}

#else

char	*ft_strrchr(const char *str, int c)
{
	char		*res;
	t_mem_word	word;

	c = (char)c;
	res = NULL;
	while (FT_MEM_ALIGN(str))
	{
		if (*str == c)
			res = (char *)str;
		if (!(*str))
			return (res);
		++str;
	}
	word = FT_MEM_WORD(c);
	while (!FT_MEM_HASZERO(*((t_mem_word *)str)
							& (*((t_mem_word *)str) ^ word)))
		str += FT_MEM_WORDLEN;
	while (1)
	{
		if (*str == c)
			res = (char *)str;
		if (!(*str))
			return (res);
		++str;
	}
}

#endif
