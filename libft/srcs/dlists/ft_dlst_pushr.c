/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_pushr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 12:19:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:46:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_pushr(t_dlist *list, t_dlist_node *new)
{
	new->prev = list->head.prev;
	new->next = &(list->head);
	new->prev->next = new;
	new->next->prev = new;
}
