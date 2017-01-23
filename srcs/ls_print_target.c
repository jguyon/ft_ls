/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_target.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:58:13 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 12:10:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void	ls_print_target(const char *target)
{
	if (target[0])
		ft_fprintf(FT_STDOUT, " -> %s", target);
}
