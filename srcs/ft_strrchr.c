/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 20:26:26 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/07 17:46:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*res;
	char	cc;

	cc = (char)c;
	res = NULL;
	while (*str)
	{
		if (*str == cc)
			res = (char *)str;
		++str;
	}
	if (*str == cc)
		res = (char *)str;
	return (res);
}
