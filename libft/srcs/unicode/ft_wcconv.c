/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcconv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:34:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 21:09:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_unicode.h"

size_t	do_wcconv(char *dst, wchar_t wc, size_t len)
{
	int		shift;
	char	c;
	size_t	count;

	if (len >= FT_WC_MAXBYTES)
		return (len);
	shift = (len == 0) ? 7 : 6 - len;
	if (wc >> shift)
	{
		c = (((char)wc) & 0b00111111) | 0b10000000;
		count = do_wcconv(dst, wc >> 6, len + 1);
		if (dst)
			dst[count] = c;
		return (count + 1);
	}
	c = (0b11111110 << shift) | ((char)wc);
	if (dst)
		dst[0] = c;
	return (1);
}

size_t	ft_wcconv(char *dst, wchar_t wc)
{
	return (do_wcconv(dst, wc, 0));
}
