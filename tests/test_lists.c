/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:09:26 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:56:54 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_libft.h"

static void	free_el(void *cnt, size_t s)
{
	(void)s;
	free(cnt);
}

static void	*expo(t_list *el, void *acc)
{
	if (*((int *)(el->content)) >= 10)
		return (NULL);
	*((int *)acc) = *((int *)acc) * 10 + *((int *)(el->content));
	return (acc);
}

TFT_TEST(test_list_fold_empty)
{
	int		n;

	n = 0;
	TFT_ASSERT(*((int *)ft_lstfoldl(NULL, &n, &expo)) == 0);
	n = 0;
	TFT_ASSERT(*((int *)ft_lstfoldr(NULL, &n, &expo)) == 0);
}

TFT_TEST(test_list_fold_iter)
{
	int		n;
	t_list	*lst;

	lst = NULL;
	n = 4;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	n = 2;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	n = 0;
	TFT_ASSERT(*((int *)ft_lstfoldl(lst, &n, &expo)) == 24);
	n = 0;
	TFT_ASSERT(*((int *)ft_lstfoldr(lst, &n, &expo)) == 42);
	ft_lstdel(&lst, &free_el);
}

TFT_TEST(test_list_fold_err)
{
	int		n;
	t_list	*lst;

	lst = NULL;
	n = 4;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	n = 10;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	n = 2;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	n = 0;
	TFT_ASSERT(((int *)ft_lstfoldl(lst, &n, &expo)) == NULL);
	TFT_ASSERT(n == 2);
	n = 0;
	TFT_ASSERT(((int *)ft_lstfoldr(lst, &n, &expo)) == NULL);
	TFT_ASSERT(n == 4);
	ft_lstdel(&lst, &free_el);
}

static int	reorder(t_list *a, t_list *b)
{
	return (*((int *)a->content) > *((int *)b->content));
}

TFT_TEST(test_list_sort)
{
	t_list	*lst;
	int		n;

	lst = NULL;
	n = 3;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	n = 4;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	n = 1;
	ft_lstadd(&lst, ft_lstnew(&n, sizeof(n)));
	ft_lstsort(&lst, &reorder);
	TFT_ASSERT(*((int *)lst->content) == 1);
	TFT_ASSERT(*((int *)lst->next->content) == 3);
	TFT_ASSERT(*((int *)lst->next->next->content) == 4);
	ft_lstdel(&lst, &free_el);
}

void	test_lists(void)
{
	TFT_RUN(test_list_fold_empty);
	TFT_RUN(test_list_fold_iter);
	TFT_RUN(test_list_fold_err);
	TFT_RUN(test_list_sort);
}
