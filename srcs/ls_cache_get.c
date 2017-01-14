/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cache_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:14:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 00:19:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_cache.h"

void	*ls_cache_get(t_cache *cache, void *val)
{
	t_dlist_node	*node;
	void			*new;

	node = ft_dlst_first(&(cache->list));
	while (node && !(cache->is(FT_DLST_ENTRY(&(cache->list), node), val)))
		node = ft_dlst_next(&(cache->list), node);
	if (node)
	{
		ft_dlst_remove(node);
		ft_dlst_pushl(&(cache->list), node);
		return (FT_DLST_ENTRY(&(cache->list), node));
	}
	if ((new = cache->new(val)))
		ft_dlst_pushl(&(cache->list), FT_DLST_NODE(&(cache->list), new));
	return (new);
}
