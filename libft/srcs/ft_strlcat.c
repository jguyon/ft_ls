/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:54:36 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/06 15:43:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t size)
{
	char	*ret;

	ret = dst;
	while (*dst && ((size_t)(dst - ret)) < size)
		++dst;
	while (*src && ((size_t)(dst - ret)) < (size - 1))
		*(dst++) = *(src++);
	if ((size_t)(dst - ret) < size)
		*dst = '\0';
	return (ft_strlen(src) + ((size_t)(dst - ret)));
}
