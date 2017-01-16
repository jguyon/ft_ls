/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 13:48:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 13:50:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include "ls_program.h"
#include <errno.h>

void	ls_print_dir(const char *name)
{
	errno = 0;
	ft_fprintf(FT_STDOUT, "%s:\n", name);
	if (ft_ferror(FT_STDOUT))
		ls_err(LS_EXIT_FAILURE, "stdout");
}
