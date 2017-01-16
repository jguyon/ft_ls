/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_target.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:58:13 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 13:08:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void	ls_print_target(const char *path, off_t size)
{
	char	*target;
	ssize_t	len;

	if (size <= 0)
		size = PATH_MAX;
	if (!(target = (char *)malloc(size + 1)))
		return ;
	len = readlink(path, target, size + 1);
	if (len < 0 || len > size)
	{
		free(target);
		return ;
	}
	ft_fprintf(FT_STDOUT, " -> %.*s", len, target);
	free(target);
}
