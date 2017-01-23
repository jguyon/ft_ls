/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_columns.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 16:25:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 18:28:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ls_tty.h"
#include "ft_printf.h"

size_t	ls_print_columns(const char *name, size_t col,
							size_t colwidth, int last)
{
	col += 1;
	if (col >= ls_tty_width() / colwidth || last)
	{
		col = 0;
		ft_fprintf(FT_STDOUT, "%s\n", name);
	}
	else
		ft_fprintf(FT_STDOUT, "%*s", -(int)colwidth, name);
	return (col);
}
