/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:40:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:02:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	char			*res;
	char			*ite;
	unsigned int	i;

	res = NULL;
	if (str && f && (res = ft_strnew(ft_strlen(str))))
	{
		ite = res;
		i = 0;
		while (*str)
			*(ite++) = f(i++, *(str++));
	}
	return (res);
}
