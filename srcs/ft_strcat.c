/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:33:22 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/04 19:35:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *restrict dst, const char *restrict src)
{
	char	*ret;

	ret = dst;
	while (*dst)
		++dst;
	while (*src)
		*(dst++) = *(src++);
	*dst = *src;
	return (ret);
}
