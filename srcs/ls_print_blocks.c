/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:54:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 12:13:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"

void	ls_print_blocks(blkcnt_t blocks, size_t blk_width,
						size_t maj_width, size_t min_width)
{
	size_t	width;

	width = (maj_width + min_width + 3) < blk_width
		? blk_width : maj_width + min_width + 3;
	ft_fprintf(FT_STDOUT, "  %*llu", (int)width, blocks);
}
