/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:43:04 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/04 19:46:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *restrict dst, const char *restrict src, size_t n)
{
	char	*ret;
	char	*mid;

	ret = dst;
	while (*dst)
		++dst;
	mid = dst;
	while (*src && ((size_t)(dst - mid)) < n)
		*(dst++) = *(src++);
	*dst = '\0';
	return (ret);
}
