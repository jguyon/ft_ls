/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 00:57:12 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:48:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_swap(t_dlist_node *n1, t_dlist_node *n2)
{
	t_dlist_node	*prev;
	t_dlist_node	*next;

	n1->prev->next = n2;
	prev = n1->prev;
	n1->prev = n2->prev;
	n1->next->prev = n2;
	next = n1->next;
	n1->next = n2->next;
	n2->prev->next = n1;
	n2->prev = prev;
	n2->next->prev = n1;
	n2->next = next;
}
