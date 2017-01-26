/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_init_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 21:57:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 21:58:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_memory.h"

void	ls_init_long(t_long_dinfo *dinfo)
{
	ft_bzero(dinfo, sizeof(*dinfo));
}
