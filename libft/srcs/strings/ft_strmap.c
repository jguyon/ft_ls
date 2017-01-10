/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:35:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 14:02:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"

char	*ft_strmap(char const *str, char (*f)(char))
{
	char	*res;
	char	*ite;

	res = NULL;
	if (str && f && (res = ft_strnew(ft_strlen(str))))
	{
		ite = res;
		while (*str)
			*(ite++) = f(*(str++));
	}
	return (res);
}
