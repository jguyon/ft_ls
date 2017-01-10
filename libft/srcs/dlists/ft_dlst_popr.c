/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_popr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 12:37:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:46:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

t_dlist_node	*ft_dlst_popr(t_dlist *list)
{
	t_dlist_node	*node;

	if (list->head.prev == &(list->head))
		return (NULL);
	node = list->head.prev;
	list->head.prev = node->prev;
	list->head.prev->next = &(list->head);
	return (node);
}
