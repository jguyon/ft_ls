/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_total.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:33:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 01:39:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ls_program.h"
#include "ft_printf.h"
#include <errno.h>

void	ls_print_total(t_long_dinfo *dinfo)
{
	errno = 0;
	if (dinfo->has_files)
	{
		if (ft_fprintf(FT_STDOUT, "total %zu\n", dinfo->total) < 0)
			ls_file_error("stdout");
	}
}
