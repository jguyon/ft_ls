/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_padl_out.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/31 12:23:12 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/31 12:39:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_padl_out(const char *s, char padc, size_t len)
{
	size_t	slen;
	size_t	plen;

	slen = ft_strnlen(s, len);
	plen = len - slen;
	while (plen)
	{
		ft_fwrite(&padc, 1, g_ls_stdout);
		--plen;
	}
	ft_fwrite(s, slen, g_ls_stdout);
	return (ft_ferror(g_ls_stdout) ? -1 : (int)len);
}
