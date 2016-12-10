/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_destroy_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 17:47:59 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 21:17:42 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_destroy_args(t_ls_args **args)
{
	if (*args)
	{
		ft_memdel((void **)&((*args)->cmd));
		ft_lstdel(&((*args)->files), ft_lstdelcnt);
		ft_memdel((void **)args);
	}
}
