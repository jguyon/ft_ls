/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write_wstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 20:25:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 22:07:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_unicode.h"
#include "priv/pf_write.h"

size_t	pf_write_wstr(t_stream *stream, const wchar_t *wstr, size_t len)
{
	size_t	i;
	size_t	l;
	char	buf[FT_WC_MAXBYTES];

	i = 0;
	while (i < len)
	{
		l = ft_wcconv(buf, *wstr);
		ft_fwrite(buf, l, stream);
		i += l;
		++wstr;
	}
	return (i);
}
