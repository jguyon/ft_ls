/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:32:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 16:07:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

#ifndef FT_MEM_OPT

size_t	ft_strlen(const char *str)
{
	const char	*end;

	end = str;
	while (*end)
		++end;
	return (end - str);
}

#else

size_t	ft_strlen(const char *str)
{
	const char	*end;

	end = str;
	while (FT_MEM_ALIGN(end))
	{
		if (!(*end))
			return (end - str);
		++end;
	}
	while (!FT_MEM_HASZERO(*((t_mem_word *)end)))
		end += FT_MEM_WORDLEN;
	while (*end)
		++end;
	return (end - str);
}

#endif
