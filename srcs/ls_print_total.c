/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_total.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:33:24 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 18:19:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include "ls_program.h"
#include <errno.h>

void	ls_print_total(t_dinfo *info)
{
	errno = 0;
	ft_fprintf(FT_STDOUT, "total %zu\n", info->total);
	if (ft_ferror(FT_STDOUT))
		ls_err(LS_EXIT_FAILURE, "stdout");
}
