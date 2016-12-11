/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_destroy_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 19:19:38 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/11 19:23:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	delfile(void *cnt, size_t size)
{
	t_ls_file	*file;

	(void)size;
	file = (t_ls_file *)cnt;
	ft_memdel((void **)&(file->name));
	ft_memdel((void **)&(file->path));
	ft_memdel((void **)&(file->stat));
	ft_memdel((void **)&file);
}

void	ls_destroy_files(t_list **files)
{
	ft_lstdel(files, &delfile);
}
