/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_insertr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 11:55:07 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:44:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_insertr(t_dlist_node *node, t_dlist_node *new)
{
	new->prev = node;
	new->next = node->next;
	new->prev->next = new;
	new->next->prev = new;
}
