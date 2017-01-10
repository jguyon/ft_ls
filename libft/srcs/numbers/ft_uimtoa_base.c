/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uimtoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:43:44 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:52:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_strings.h"
#include "ft_numbers.h"

static char	to_base(unsigned int dgt, char a)
{
	return (dgt < 10 ? dgt + '0' : (dgt % 10) + a);
}

char		*ft_uimtoa_base(uintmax_t n, unsigned int base, int upper, int prec)
{
	char		*str;
	size_t		i;
	uintmax_t	m;
	char		a;

	if (base < 2 || base > 16)
		return (NULL);
	i = 1;
	m = n;
	while (m /= base)
		++i;
	if (prec >= 0 && (prec - (int)i > 0 || n == 0))
		i = prec;
	if (!(str = ft_strnew(i)))
		return (NULL);
	m = n;
	a = upper ? 'A' : 'a';
	while (i--)
	{
		str[i] = to_base(m % base, a);
		m /= base;
	}
	return (str);
}
