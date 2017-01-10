/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_splicer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 19:44:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:48:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_splicer(t_dlist_node *node, t_dlist *list)
{
	list->head.prev->next = node->next;
	list->head.next->prev = node;
	node->next->prev = list->head.prev;
	node->next = list->head.next;
}
