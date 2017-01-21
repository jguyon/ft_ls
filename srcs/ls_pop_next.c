/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_pop_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 16:50:00 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 12:15:23 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file	*ls_pop_next(t_flags flags, t_dlist *dirs)
{
	t_dlist_node	*node;

	if (flags.reverse)
		node = ft_dlst_popr(dirs);
	else
		node = ft_dlst_popl(dirs);
	if (!node)
		return (NULL);
	return (FT_DLST_ENTRY(dirs, node));
}
