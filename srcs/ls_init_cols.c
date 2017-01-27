/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_init_cols.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:18:03 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 14:19:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_memory.h"

void	ls_init_cols(t_cols_dinfo *dinfo)
{
	ft_bzero(dinfo, sizeof(*dinfo));
}
