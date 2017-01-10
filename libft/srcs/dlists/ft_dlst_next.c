/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_next.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 13:03:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:45:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

t_dlist_node	*ft_dlst_next(t_dlist *list, t_dlist_node *node)
{
	if (node->next == &(list->head))
		return (NULL);
	return (node->next);
}
