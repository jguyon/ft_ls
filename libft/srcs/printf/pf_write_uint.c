/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:47:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 19:02:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_write.h"
#include "priv/pf_defs.h"
#include "ft_chars.h"

static char	to_digit(unsigned char dgt, int base)
{
	if (dgt < 10)
		return (dgt + '0');
	else if (base < 0)
		return (dgt - 10 + 'A');
	else
		return (dgt - 10 + 'a');
}

size_t		pf_write_uint(t_stream *stream, uintmax_t n, int base, size_t len)
{
	char	str[sizeof(uintmax_t) * 8];
	char	*dgt;
	size_t	i;

	dgt = &(str[sizeof(str) - 1]);
	i = 0;
	while (n)
	{
		*dgt = to_digit(n % PF_ABS(base), base);
		n /= PF_ABS(base);
		--dgt;
		++i;
	}
	while (i < len)
	{
		*dgt = '0';
		--dgt;
		++i;
	}
	ft_fwrite(dgt + 1, len, stream);
	return (len);
}
