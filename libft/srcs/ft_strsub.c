/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:34:35 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/06 16:48:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *str, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;

	sub = NULL;
	if (str && (sub = ft_strnew(len)))
	{
		i = 0;
		while (i < len)
		{
			sub[i] = str[start + i];
			++i;
		}
	}
	return (sub);
}
