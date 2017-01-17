/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_uintmax_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 19:10:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 19:12:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_convert.h"

size_t	pf_uintmax_len(uintmax_t n, int prec, unsigned int base)
{
	size_t	len;

	len = 0;
	if (prec < 0)
		prec = 1;
	while (n)
	{
		n /= base;
		++len;
	}
	return (len < (size_t)prec ? (size_t)prec : len);
}
