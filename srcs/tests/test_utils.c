/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 22:03:19 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 00:02:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_ls.h"

TLS_TEST(test_util_join_path)
{
	char	*str;

	TLS_ASSERT((str = ls_join_path("dir", "file")));
	TLS_ASSERT(str && strcmp(str, "dir/file") == 0);
	free(str);
	TLS_ASSERT((str = ls_join_path("dir/", "file")));
	TLS_ASSERT(str && strcmp(str, "dir/file") == 0);
	free(str);
	TLS_ASSERT((str = ls_join_path("/some/dir", "file")));
	TLS_ASSERT(str && strcmp(str, "/some/dir/file") == 0);
	free(str);
	TLS_ASSERT((str = ls_join_path("/some/dir/", "file")));
	TLS_ASSERT(str && strcmp(str, "/some/dir/file") == 0);
	free(str);
	TLS_ASSERT((str = ls_join_path("", "file")));
	TLS_ASSERT(str && strcmp(str, "file") == 0);
	free(str);
}

static t_list	*fname_create(const char *name)
{
	t_ls_file	f;

	f.path = NULL;
	f.stat = NULL;
	f.name = ft_strdup(name);
	return (ft_lstnew(&f, sizeof(f)));
}

TLS_TEST(test_util_lexi_cmp)
{
	t_list		*e1;
	t_list		*e2;

	TLS_ASSERT(!ls_lexi_cmp((e1 = fname_create("abc")), (e2 = fname_create("abd"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(ls_lexi_cmp((e1 = fname_create("abc")), (e2 = fname_create("abb"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(!ls_lexi_cmp((e1 = fname_create("abc")), (e2 = fname_create("abc"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
}

TLS_TEST(test_util_lexi_revcmp)
{
	t_list		*e1;
	t_list		*e2;

	TLS_ASSERT(ls_lexi_revcmp((e1 = fname_create("abc")), (e2 = fname_create("abd"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(!ls_lexi_revcmp((e1 = fname_create("abc")), (e2 = fname_create("abb"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(ls_lexi_revcmp((e1 = fname_create("abc")), (e2 = fname_create("abc"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
}

static t_list	*mtime_create(time_t t, const char *name)
{
	t_ls_file	f;

	f.path = NULL;
	f.name = ft_strdup(name);
	f.stat = (struct stat *)ft_memalloc(sizeof(*(f.stat)));
	f.stat->st_mtime = t;
	return (ft_lstnew(&f, sizeof(f)));
}

TLS_TEST(test_util_modt_cmp)
{
	t_list		*e1;
	t_list		*e2;
	time_t		t;

	t = time(NULL);
	TLS_ASSERT(!ls_modt_cmp((e1 = mtime_create(t + 1, "b")), (e2 = mtime_create(t, "a"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(ls_modt_cmp((e1 = mtime_create(t, "a")), (e2 = mtime_create(t + 1, "b"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(ls_modt_cmp((e1 = mtime_create(t, "b")), (e2 = mtime_create(t, "a"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(!ls_modt_cmp((e1 = mtime_create(t, "a")), (e2 = mtime_create(t, "a"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
}

TLS_TEST(test_util_modt_revcmp)
{
	t_list		*e1;
	t_list		*e2;
	time_t		t;

	t = time(NULL);
	TLS_ASSERT(ls_modt_revcmp((e1 = mtime_create(t + 1, "b")), (e2 = mtime_create(t, "a"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(!ls_modt_revcmp((e1 = mtime_create(t, "a")), (e2 = mtime_create(t + 1, "b"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(!ls_modt_revcmp((e1 = mtime_create(t, "b")), (e2 = mtime_create(t, "a"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
	TLS_ASSERT(ls_modt_revcmp((e1 = mtime_create(t, "a")), (e2 = mtime_create(t, "a"))));
	ls_destroy_files(&e1);
	ls_destroy_files(&e2);
}

TLS_TEST(test_util_sort_fun)
{
	unsigned int	flags;

	flags = 0;
	TLS_ASSERT(ls_sort_fun(flags) == &ls_lexi_cmp);
	LS_ADD_FLAG(flags, LS_FLAG_REV);
	TLS_ASSERT(ls_sort_fun(flags) == &ls_lexi_revcmp);
	flags = 0;
	LS_ADD_FLAG(flags, LS_FLAG_TME);
	TLS_ASSERT(ls_sort_fun(flags) == &ls_modt_cmp);
	LS_ADD_FLAG(flags, LS_FLAG_REV);
	TLS_ASSERT(ls_sort_fun(flags) == &ls_modt_revcmp);
}

void	test_utils(void)
{
	TLS_RUN(test_util_join_path);
	TLS_RUN(test_util_lexi_cmp);
	TLS_RUN(test_util_lexi_revcmp);
	TLS_RUN(test_util_modt_cmp);
	TLS_RUN(test_util_modt_revcmp);
	TLS_RUN(test_util_sort_fun);
}
