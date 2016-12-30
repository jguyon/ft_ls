/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 21:36:50 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 11:43:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r');
}

static int	strtoi(const char *str)
{
	unsigned int	n;

	n = 0;
	while (ft_isdigit(*str))
	{
		n = 10 * n + *str - '0';
		++str;
	}
	return ((int)n);
}

int			ft_atoi(const char *str)
{
	int				sign;

	while (is_space(*str))
		++str;
	sign = *str == '-' ? -1 : 1;
	if (sign == -1 || *str == '+')
		++str;
	return (strtoi(str) * sign);
}
