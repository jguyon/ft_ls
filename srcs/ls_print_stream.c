/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_stream.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 13:16:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 13:52:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_strings.h"
#include "ft_streams.h"

size_t	ls_print_stream(const char *name, size_t col, int last, size_t width)
{
	size_t	len;

	len = ft_strlen(name);
	if (col + len + 2 > width)
	{
		ft_fputc('\n', FT_STDOUT);
		col = 0;
	}
	ft_fputs(name, FT_STDOUT);
	col += len;
	if (last)
	{
		ft_fputc('\n', FT_STDOUT);
		col = 0;
	}
	else
	{
		ft_fputs(", ", FT_STDOUT);
		col += 2;
	}
	return (col);
}
