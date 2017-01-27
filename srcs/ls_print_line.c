/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:56:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 19:42:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_streams.h"

int		ls_print_line(void *dirinfo, t_file *file)
{
	(void)dirinfo;
	if (g_print_name(file) || (g_print_suffix && g_print_suffix(file) < 0))
		return (-1);
	ft_fputc('\n', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}
