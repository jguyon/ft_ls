/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_destroy_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 17:47:59 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 19:52:00 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_destroy_args(t_ls_args **args)
{
	if (*args)
	{
		ls_destroy_files(&((*args)->files));
		ls_destroy_files(&((*args)->dirs));
		ft_memdel((void **)&((*args)->dinfo));
		ft_memdel((void **)args);
	}
}
