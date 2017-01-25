/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:31:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 13:35:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ls_program.h"
#include "ft_streams.h"

int		g_ls_status = LS_EXIT_SUCCESS;

void	ls_file_error(const char *name)
{
	g_ls_status = LS_EXIT_FAILURE;
	if (ft_ferror(FT_STDOUT))
		ls_err(g_ls_status, "stdout");
	else
		ls_warn("%s", name);
}
