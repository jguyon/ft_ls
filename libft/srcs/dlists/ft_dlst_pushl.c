/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_pushl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 12:16:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:46:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_pushl(t_dlist *list, t_dlist_node *new)
{
	new->prev = &(list->head);
	new->next = list->head.next;
	new->prev->next = new;
	new->next->prev = new;
}
