/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 18:52:18 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 17:22:44 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_strings.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*ret;

	ret = dst;
	if ((dst = ft_memccpy(dst, src, '\0', n)))
		ft_bzero(dst, n - (dst - ret));
	return (ret);
}
