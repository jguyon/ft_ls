/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_destroy_finfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 20:59:01 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 16:47:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_destroy_finfo(t_ls_finfo **finfo)
{
	if (*finfo)
	{
		ft_memdel((void **)&((*finfo)->mode));
		ft_memdel((void **)&((*finfo)->links));
		ft_memdel((void **)&((*finfo)->owner));
		ft_memdel((void **)&((*finfo)->group));
		ft_memdel((void **)&((*finfo)->size));
		ft_memdel((void **)&((*finfo)->time));
		ft_memdel((void **)&((*finfo)->dest));
		ft_memdel((void **)&((*finfo)->dmaj));
		ft_memdel((void **)&((*finfo)->dmin));
	}
	ft_memdel((void **)finfo);
}
