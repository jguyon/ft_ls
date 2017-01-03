/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:32:40 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 01:37:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "libft/ft_strings.h"

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
