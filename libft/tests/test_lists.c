/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:09:26 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/18 18:24:48 by jguyon           ###   ########.fr       */
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

static void	*el_at(t_list *lst, size_t i)
{
	if (!lst)
		return (NULL);
	if (i == 0)
		return (lst->content);
	return (el_at(lst->next, i - 1));
}

TFT_TEST(test_list_sort)
{
	t_list	*lst;
	int		n[6] = {1, 4, 3, 0, 1, 1};

	lst = NULL;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 5;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 4;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 3;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 2;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 1;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n;
	ft_lstsort(&lst, &reorder);
	TFT_ASSERT(el_at(lst, 0) == n + 3);
	TFT_ASSERT(el_at(lst, 1) == n + 0);
	TFT_ASSERT(el_at(lst, 2) == n + 4);
	TFT_ASSERT(el_at(lst, 3) == n + 5);
	TFT_ASSERT(el_at(lst, 4) == n + 2);
	TFT_ASSERT(el_at(lst, 5) == n + 1);
	ft_lstdel(&lst, NULL);
}

TFT_TEST(test_list_msort)
{
	t_list	*lst;
	int		n[6] = {1, 4, 3, 0, 1, 1};

	lst = NULL;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 5;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 4;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 3;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 2;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n + 1;
	ft_lstadd(&lst, ft_lstnew(0, 0));
	lst->content = n;
	ft_lstmsort(&lst, &reorder);
	TFT_ASSERT(el_at(lst, 0) == n + 3);
	TFT_ASSERT(el_at(lst, 1) == n + 0);
	TFT_ASSERT(el_at(lst, 2) == n + 4);
	TFT_ASSERT(el_at(lst, 3) == n + 5);
	TFT_ASSERT(el_at(lst, 4) == n + 2);
	TFT_ASSERT(el_at(lst, 5) == n + 1);
	ft_lstdel(&lst, NULL);
}

void	test_lists(void)
{
	TFT_RUN(test_list_fold_empty);
	TFT_RUN(test_list_fold_iter);
	TFT_RUN(test_list_fold_err);
	TFT_RUN(test_list_sort);
	TFT_RUN(test_list_msort);
}
