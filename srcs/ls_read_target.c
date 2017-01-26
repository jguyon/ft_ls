/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_read_target.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 23:02:07 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 01:33:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include <stdlib.h>
#include <unistd.h>

size_t	ls_target_size(struct stat *st)
{
	if (st->st_size == 0)
		return (PATH_MAX);
	else
		return (st->st_size);
}

int		ls_read_target(char *dst, const char *path, size_t size)
{
	ssize_t	res;

	res = readlink(path, dst, size + 1);
	if (res < 0 || (size_t)res > size)
		return (-1);
	dst[res] = '\0';
	return (0);
}
