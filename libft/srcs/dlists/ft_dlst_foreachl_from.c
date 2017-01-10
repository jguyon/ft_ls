/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_foreachl_from.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 11:58:57 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:43:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_foreachl_from(t_dlist *list, t_dlist_node *first, void *acc,
								t_dlist_iterator itr)
{
	first = first->next;
	while (first->prev != &(list->head)
			&& itr(FT_DLST_ENTRY(list, first->prev), acc))
		first = first->next;
}
