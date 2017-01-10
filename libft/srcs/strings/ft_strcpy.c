/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:42:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:01:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

char	*ft_strcpy(char *dst, const char *src)
{
	char	*ret;

	ret = dst;
	while (FT_MEM_ALIGN(src))
	{
		if (!(*(dst++) = *(src++)))
			return (ret);
	}
	while (!FT_MEM_HASZERO(*((t_mem_word *)src)))
	{
		*((t_mem_word *)dst) = *((t_mem_word *)src);
		src += FT_MEM_WORDLEN;
		dst += FT_MEM_WORDLEN;
	}
	while ((*(dst++) = *(src++)))
		;
	return (ret);
}
