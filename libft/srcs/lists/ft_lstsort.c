/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:01:58 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:50:21 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists.h"

static int	sort_list(t_list **list, int is_sorted,
						int (*order)(t_list *, t_list *))
{
	t_list	*t1;
	t_list	*t2;

	if (!(*list) || !((*list)->next))
		return (is_sorted);
	if (order(*list, (*list)->next))
	{
		t1 = *list;
		t2 = (*list)->next;
		t1->next = t2->next;
		t2->next = t1;
		*list = t2;
		return (sort_list(&((*list)->next), 0, order));
	}
	return (sort_list(&((*list)->next), is_sorted, order));
}

void		ft_lstsort(t_list **lst, int (*f)(t_list *e1, t_list *e2))
{
	while (!(sort_list(lst, 1, f)))
		;
}
