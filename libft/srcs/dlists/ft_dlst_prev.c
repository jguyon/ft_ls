/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_prev.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 13:02:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:46:15 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

t_dlist_node	*ft_dlst_prev(t_dlist *list, t_dlist_node *node)
{
	if (node->prev == &(list->head))
		return (NULL);
	return (node->prev);
}
