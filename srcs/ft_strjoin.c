/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:38:31 by jguyon            #+#    #+#             */
/*   Updated: 2016/11/06 16:48:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;

	join = NULL;
	if (s1 && s2 && (join = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
	{
		ft_strcpy(join, s1);
		ft_strcat(join, s2);
	}
	return (join);
}
