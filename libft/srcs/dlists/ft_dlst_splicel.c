/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_splicel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 19:38:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:47:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_splicel(t_dlist_node *node, t_dlist *list)
{
	list->head.prev->next = node;
	list->head.next->prev = node->prev;
	node->prev->next = list->head.next;
	node->prev = list->head.prev;
}
