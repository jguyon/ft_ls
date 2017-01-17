/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:22:59 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 17:00:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

#ifndef FT_MEM_OPT

void	ft_strclr(char *str)
{
	if (!str)
		return ;
	while (*str)
		*(str++) = 0;
}

#else

void	ft_strclr(char *str)
{
	if (!str)
		return ;
	while (FT_MEM_ALIGN(str))
	{
		if (!(*str))
			return ;
		*(str++) = 0;
	}
	while (!FT_MEM_HASZERO(*((t_mem_word *)str)))
	{
		*((t_mem_word *)str) = 0;
		str += FT_MEM_WORDLEN;
	}
	while (*str)
		*(str++) = 0;
}

#endif
