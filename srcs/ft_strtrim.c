/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:46:27 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/06 16:49:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *str)
{
	unsigned int	start;
	size_t			len;

	if (!str)
		return (NULL);
	start = 0;
	while (is_space(str[start]))
		++start;
	len = ft_strlen(str + start);
	while (len > 0 && is_space(str[start + len - 1]))
		--len;
	return (ft_strsub(str, start, len));
}
