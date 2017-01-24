/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_del.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 15:09:53 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 23:28:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_files.h"
#include "ft_memory.h"
#include <stdlib.h>

void	ls_file_del(t_file **file)
{
	free((*file)->path);
	if ((*file)->stat != (*file)->lstat)
		free((*file)->stat);
	free((*file)->lstat);
	if ((*file)->del && (*file)->info)
		(*file)->del((*file)->info);
	ft_memdel((void **)file);
}
