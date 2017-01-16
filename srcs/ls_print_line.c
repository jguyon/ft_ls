/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:56:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 13:20:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_streams.h"

void	ls_print_line(const char *name)
{
	ft_fputs(name, FT_STDOUT);
	ft_fputc('\n', FT_STDOUT);
}
