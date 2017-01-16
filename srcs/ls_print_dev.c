/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_dev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:58:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 12:18:11 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"

void	ls_print_dev(dev_t dev, size_t blk_width,
						size_t maj_width, size_t min_width)
{
	maj_width = min_width + maj_width + 3 < blk_width
		? blk_width - min_width - 3 : maj_width;
	ft_fprintf(FT_STDOUT, "   %*u, %*u", (int)maj_width, LS_MAJOR(dev),
				(int)min_width, LS_MINOR(dev));
}
