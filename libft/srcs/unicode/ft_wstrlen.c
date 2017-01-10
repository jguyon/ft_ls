/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:37:36 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:04:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_unicode.h"

size_t	ft_wstrlen(const wchar_t *str)
{
	size_t	len;

	len = 0;
	while (*str != L'\0')
	{
		len += ft_wclen(*str);
		++str;
	}
	return (len);
}
