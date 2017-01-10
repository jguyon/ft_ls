/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_popl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 12:30:59 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:45:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

t_dlist_node	*ft_dlst_popl(t_dlist *list)
{
	t_dlist_node	*node;

	if (list->head.next == &(list->head))
		return (NULL);
	node = list->head.next;
	list->head.next = node->next;
	list->head.next->prev = &(list->head);
	return (node);
}
