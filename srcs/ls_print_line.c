/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:56:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 13:52:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_streams.h"
#include "ls_program.h"
#include <errno.h>

void	ls_print_line(const char *name)
{
	errno = 0;
	ft_fputs(name, FT_STDOUT);
	ft_fputc('\n', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		ls_err(LS_EXIT_FAILURE, "stdout");
}