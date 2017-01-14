/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cache_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 22:26:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/14 22:30:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_cache.h"

void	ls_cache_clear(t_cache *cache)
{
	t_dlist_node	*node;

	while ((node = ft_dlst_popl(&(cache->list))))
		cache->del(FT_DLST_ENTRY(&(cache->list), node));
}
