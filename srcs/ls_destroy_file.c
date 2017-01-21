/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_destroy_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:07:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 16:39:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdlib.h>

void	ls_destroy_file(t_file *file)
{
	if (file)
	{
		free(file->stat);
		free(file->info);
		free((void *)(file->path));
		free(file);
	}
}
