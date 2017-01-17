/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:54:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 11:05:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"

void	ls_print_size(off_t size, size_t size_width,
						size_t maj_width, size_t min_width)
{
	size_t	width;

	width = (maj_width == 0 && min_width == 0)
			|| (maj_width + min_width + 3) < size_width
				? size_width : maj_width + min_width + 3;
	ft_fprintf(FT_STDOUT, "  %*llu", (int)width, size);
}
