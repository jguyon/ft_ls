/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:57:32 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/07 17:22:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	uc;
	unsigned char	*ustr;

	uc = (unsigned char)c;
	ustr = (unsigned char *)str;
	i = 0;
	while (i < len)
	{
		ustr[i] = uc;
		++i;
	}
	return (str);
}
