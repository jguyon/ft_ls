/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_nlink.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:33:51 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 11:38:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include <inttypes.h>

void	ls_print_nlink(nlink_t nlink, size_t width)
{
	ft_fprintf(FT_STDOUT, " %*ju", width, (uintmax_t)nlink);
}
