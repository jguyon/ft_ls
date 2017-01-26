/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:56:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 13:14:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_streams.h"

int		ls_print_line(void *dirinfo, t_file *file)
{
	(void)dirinfo;
	g_print_name(file);
	ft_fputc('\n', FT_STDOUT);
	if (ft_ferror(FT_STDOUT))
		return (-1);
	return (0);
}
