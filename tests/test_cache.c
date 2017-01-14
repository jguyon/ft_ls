/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cache.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 23:54:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 00:09:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_cache.h"

typedef struct	s_num {
	int				n;
	t_dlist_node	node;
}				t_num;

static int	num_is(void *entry, void *val)
{
	return (*((int *)entry) == *((int *)val));
}

static void	*num_new(void *val)
{
	t_num	*entry;

	if (!(entry = (t_num *)malloc(sizeof(*entry))))
		return (NULL);
	entry->n = *((int *)val);
	return (entry);
}

static void	num_del(void *entry)
{
	free(entry);
}

TLS_TEST(test_cache_get_entry)
{
	t_cache	cache = {
		.is = &num_is,
		.new = &num_new,
		.del = &num_del,
		.list = LS_DLST(cache.list, t_num, node),
	};
	int		n;
	t_num	*entry;

	n = 0;
	entry = ls_cache_get(&cache, &n);
	TLS_ASSERT(entry && entry->n == n);
	n = 2;
	entry = ls_cache_get(&cache, &n);
	TLS_ASSERT(entry && entry->n == n);
	n = 0;
	entry = ls_cache_get(&cache, &n);
	TLS_ASSERT(entry && entry->n == n);
	ls_cache_clear(&cache);
}

void	test_cache(void)
{
	TLS_RUN(test_cache_get_entry);
}
