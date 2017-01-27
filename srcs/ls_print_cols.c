/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_cols.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:34:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 19:40:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_printf.h"
#include "ft_strings.h"

int		ls_print_cols(t_cols_dinfo *dinfo, t_file *file)
{
	int		has_suffix;

	has_suffix = 0;
	if (g_print_name(file)
		|| (g_print_suffix && (has_suffix = g_print_suffix(file)) < 0))
		return (-1);
	++(dinfo->x);
	if (dinfo->x == dinfo->cols
		|| (dinfo->x + 1 == dinfo->cols
			&& dinfo->y >= (dinfo->count - 1) % dinfo->rows + 1))
	{
		dinfo->x = 0;
		++(dinfo->y);
		ft_fputc('\n', FT_STDOUT);
	}
	else
		ft_fprintf(FT_STDOUT, "%*s",
					dinfo->colwidth - ft_strlen(file->name) - has_suffix, "");
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}
