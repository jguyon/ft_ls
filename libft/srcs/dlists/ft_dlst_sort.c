/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 13:24:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:47:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memory.h"
#include "ft_dlists.h"

/*
** Merge two sorted null-terminated linked lists together
*/

static t_dlist_node	*merge_lists(t_dlist *list,
									t_dlist_node *left, t_dlist_node *right,
									t_dlist_compare cmp)
{
	t_dlist_node	*merged;
	t_dlist_node	**curr;

	merged = NULL;
	curr = &merged;
	while (left && right)
	{
		if (cmp(FT_DLST_ENTRY(list, left), FT_DLST_ENTRY(list, right)) > 0)
		{
			*curr = right;
			right = right->next;
		}
		else
		{
			*curr = left;
			left = left->next;
		}
		curr = &((*curr)->next);
	}
	*curr = left ? left : right;
	return (merged);
}

/*
** Merge the next node and iteratively merge resulting list parts
*/

static void			merge_parts(t_dlist *list, t_dlist_node **parts,
								t_dlist_node *node, t_dlist_compare cmp)
{
	size_t	i;

	i = 0;
	while (i < FT_DLST_SORT_PARTS && parts[i])
	{
		node = merge_lists(list, parts[i], node, cmp);
		parts[i++] = NULL;
	}
	if (i > FT_DLST_SORT_PARTS)
		--i;
	parts[i] = node;
}

/*
** Merge all remaining list parts and restore missing links
*/

static void			merge_all_parts(t_dlist *list, t_dlist_node **parts,
									t_dlist_compare cmp)
{
	t_dlist_node	*merged;
	size_t			i;

	i = 0;
	merged = NULL;
	while (i < FT_DLST_SORT_PARTS)
		merged = merge_lists(list, parts[i++], merged, cmp);
	list->head.next = merged;
	merged->prev = &(list->head);
	while (merged->next)
	{
		merged->next->prev = merged;
		merged = merged->next;
	}
	list->head.prev = merged;
	merged->next = &(list->head);
}

/*
** Merge sort algorithm
**
** The circular doubly-linked list is sorted as a standard null-terminated one
** before being converted back to avoid having to keep
** the prev links up to date.
*/

void				ft_dlst_sort(t_dlist *list, t_dlist_compare cmp)
{
	t_dlist_node	*parts[FT_DLST_SORT_PARTS];
	t_dlist_node	*result;
	t_dlist_node	*next;

	if (list->head.next == &(list->head) || list->head.next == list->head.prev)
		return ;
	ft_bzero(parts, sizeof(parts));
	list->head.prev->next = NULL;
	result = list->head.next;
	while (result)
	{
		next = result->next;
		result->next = NULL;
		merge_parts(list, parts, result, cmp);
		result = next;
	}
	merge_all_parts(list, parts, cmp);
}
