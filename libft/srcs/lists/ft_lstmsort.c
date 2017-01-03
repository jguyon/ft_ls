/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmsort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 17:09:56 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 02:53:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_lists.h"

static void		empty_into_list(t_list **dest, t_list *lst)
{
	t_list	**curr;
	t_list	*next;

	curr = dest;
	while (lst)
	{
		next = lst->next;
		ft_lstadd(curr, lst);
		lst = next;
		curr = &((*curr)->next);
	}
}

static t_list	*merge_lists(t_list *left, t_list *right,
								int (*f)(t_list *e1, t_list *e2))
{
	t_list	*merged;
	t_list	**curr;
	t_list	*next;

	merged = NULL;
	curr = &merged;
	while (left && right)
	{
		if (f(left, right))
		{
			next = right->next;
			ft_lstadd(curr, right);
			right = next;
		}
		else
		{
			next = left->next;
			ft_lstadd(curr, left);
			left = next;
		}
		curr = &((*curr)->next);
	}
	empty_into_list(curr, left);
	empty_into_list(curr, right);
	return (merged);
}

size_t			partition_list(t_list *lst, t_list **left, t_list **right,
								size_t i)
{
	size_t	j;

	if (!lst)
		return (0);
	j = partition_list(lst->next, left, right, i + 1);
	if (i <= j)
		ft_lstadd(left, lst);
	else
		ft_lstadd(right, lst);
	return (j + 1);
}

void			ft_lstmsort(t_list **lst, int (*f)(t_list *e1, t_list *e2))
{
	t_list	*left;
	t_list	*right;

	if (!(*lst) || !((*lst)->next))
		return ;
	left = NULL;
	right = NULL;
	partition_list(*lst, &left, &right, 0);
	ft_lstmsort(&left, f);
	ft_lstmsort(&right, f);
	*lst = merge_lists(left, right, f);
}
