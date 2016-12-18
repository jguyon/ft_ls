/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 15:36:08 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/04 15:45:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(str) + 1;
	if (!(dup = (char *)malloc(len * sizeof(*dup))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = str[i];
		++i;
	}
	return (dup);
}
