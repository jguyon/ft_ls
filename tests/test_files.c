/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:10:06 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 14:01:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_files.h"
#include "ls_program.h"
#include "ft_printf.h"
#include "ft_strings.h"

static void	count_init(size_t *count)
{
	*count = 0;
}

static void count_del(time_t *i)
{
	free(i);
}

static int	count_insert(size_t *count, t_file *file)
{
	if (ls_file_lstat(file))
		return (-1);
	file->info = malloc(sizeof(time_t));
	*((time_t *)(file->info)) = file->lstat->st_mtime;
	file->del = (t_file_del *)(&count_del);
	if (count)
		++(*count);
	return (0);
}

static void	count_print(size_t *count, t_dlist *files)
{
	t_dlist_node	*node;
	t_file			*file;

	node = ft_dlst_first(files);
	while (node)
	{
		file = FT_DLST_ENTRY(files, node);
		ft_fprintf(FT_STDOUT, "%s, %ld, %zu\n", file->name, (long)*((time_t *)file->info), *count);
		node = ft_dlst_next(files, node);
	}
}

static int	count_compare(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f1->name, f2->name));
}

static int	count_reject(const char *name)
{
	return (ft_strcmp(name, ".") == 0 || ft_strcmp(name, "..") == 0);
}

static void	count_error(const char *name)
{
	ls_warn("%s", name);
}

static void	count_config(t_flist *flist, size_t *count)
{
	bzero(flist, sizeof(*flist));
	flist->dirinfo = count;
	flist->init = (t_flist_init *)(&count_init);
	flist->insert = (t_flist_insert *)(&count_insert);
	flist->print = (t_flist_print *)(&count_print);
	flist->compare = &count_compare;
	flist->reject = &count_reject;
	flist->error = &count_error;
}

TLS_TEST(test_files_traverse)
{
	t_flist		flist;
	size_t		count;
	t_file		*next;

	count = 0;
	count_config(&flist, &count);
	TLS_ASSERT(!ls_flist_init(&flist));
	TLS_INIT_FS;
	TLS_MKDIR("a");
	TLS_MKDIR("b");
	TLS_TOUCHT("197001010000.01", "0");
	TLS_TOUCHT("197001010000.02", "1");
	TLS_TOUCHT("197001010000.02", "a/1");
	TLS_TOUCHT("197001010000.04", "a/3");
	TLS_MKDIR("a/0");
	TLS_TOUCHT("197001010000.01", "a/0");
	ls_flist_add(&flist, TLS_DIR "b", 0, 0);
	ls_flist_add(&flist, TLS_DIR "a", 0, 0);
	ls_flist_add(&flist, TLS_DIR "1", 0, 0);
	ls_flist_add(&flist, TLS_DIR "0", 0, 0);
	ls_flist_start(&flist);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp(TLS_DIR "0, 1, 2\n" TLS_DIR "1, 2, 2\n"));
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "a") == 0);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp("0, 1, 3\n1, 2, 3\n3, 4, 3\n"));
	ls_file_del(&next);
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "b") == 0);
	TLS_ASSERT(!ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp(""));
	ls_file_del(&next);
	TLS_ASSERT(!ls_flist_next(&flist, NULL));
	TLS_ASSERT(tls_errcmp(""));
	ls_flist_clear(&flist);
	TLS_STOP_FS;
}

TLS_TEST(test_files_errors)
{
	t_flist		flist;
	size_t		count;
	t_file		*next;

	count = 0;
	count_config(&flist, &count);
	TLS_ASSERT(!ls_flist_init(&flist));
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_MKDIR("otherdir");
	ls_flist_add(&flist, TLS_DIR "none", 0, 0);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "none: No such file or directory\n"));
	ls_flist_add(&flist, TLS_DIR "dir", 0, 0);
	ls_flist_add(&flist, TLS_DIR "otherdir", 0, 0);
	TLS_ASSERT(tls_errcmp(""));
	ls_flist_start(&flist);
	TLS_CHMOD("000", "dir");
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "dir") == 0);
	ls_file_del(&next);
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "otherdir") == 0);
	ls_file_del(&next);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "dir: Permission denied\n"));
	ls_flist_clear(&flist);
	TLS_CHMOD("777", "dir");
	TLS_STOP_FS;
}

TLS_TEST(test_files_reverse)
{
	t_flist		flist;
	size_t		count;
	t_file		*next;

	count = 0;
	count_config(&flist, &count);
	flist.reverse = 1;
	TLS_ASSERT(!ls_flist_init(&flist));
	TLS_INIT_FS;
	TLS_MKDIR("a");
	TLS_MKDIR("b");
	TLS_TOUCHT("197001010000.01", "0");
	TLS_TOUCHT("197001010000.02", "1");
	TLS_TOUCHT("197001010000.02", "a/1");
	TLS_TOUCHT("197001010000.04", "a/3");
	TLS_TOUCHT("197001010000.01", "a/0");
	ls_flist_add(&flist, TLS_DIR "a", 0, 0);
	ls_flist_add(&flist, TLS_DIR "b", 0, 0);
	ls_flist_add(&flist, TLS_DIR "0", 0, 0);
	ls_flist_add(&flist, TLS_DIR "1", 0, 0);
	ls_flist_start(&flist);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp(TLS_DIR "1, 2, 2\n" TLS_DIR "0, 1, 2\n"));
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "b") == 0);
	TLS_ASSERT(!ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp(""));
	ls_file_del(&next);
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "a") == 0);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp("3, 4, 3\n1, 2, 3\n0, 1, 3\n"));
	ls_file_del(&next);
	TLS_ASSERT(!ls_flist_next(&flist, NULL));
	TLS_ASSERT(tls_errcmp(""));
	ls_flist_clear(&flist);
	TLS_STOP_FS;
}

TLS_TEST(test_files_recursive)
{
	t_flist		flist;
	size_t		count;
	t_file		*next;

	count = 0;
	count_config(&flist, &count);
	flist.recur = 1;
	TLS_ASSERT(!ls_flist_init(&flist));
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_MKDIR("dir/dir1");
	TLS_TOUCHT("197001010000.00", "dir/dir1/file1");
	TLS_TOUCHT("197001010000.00", "dir/dir1");
	TLS_MKDIR("dir/dir2");
	TLS_TOUCHT("197001010000.00", "dir/dir2/file2");
	TLS_TOUCHT("197001010000.00", "dir/dir2");
	ls_flist_add(&flist, TLS_DIR "dir", 0, 0);
	ls_flist_start(&flist);
	TLS_ASSERT(!ls_flist_print(&flist));
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "dir") == 0);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp("dir1, 0, 2\ndir2, 0, 2\n"));
	ls_file_del(&next);
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, "dir1") == 0);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT((tls_outcmp("file1, 0, 1\n")));
	ls_file_del(&next);
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, "dir2") == 0);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT((tls_outcmp("file2, 0, 1\n")));
	ls_file_del(&next);
	TLS_ASSERT(!ls_flist_next(&flist, NULL));
	TLS_ASSERT(tls_errcmp(""));
	ls_flist_clear(&flist);
	TLS_STOP_FS;
}

TLS_TEST(test_files_nofollow)
{
	t_flist		flist;
	size_t		count;
	t_file		*next;

	count = 0;
	count_config(&flist, &count);
	TLS_ASSERT(!ls_flist_init(&flist));
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCHT("197001010000.00", "dir/file");
	TLS_LNS("dir", "lnk");
	TLS_TOUCHT("197001010000.00 -h", "lnk");
	ls_flist_add(&flist, TLS_DIR "lnk", 0, 0);
	ls_flist_start(&flist);
	TLS_ASSERT(!ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp(""));
	TLS_ASSERT((next = ls_flist_next(&flist, NULL)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "lnk") == 0);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp("file, 0, 1\n"));
	ls_file_del(&next);
	TLS_ASSERT(!ls_flist_next(&flist, NULL));
	TLS_ASSERT(tls_errcmp(""));
	ls_flist_clear(&flist);
	TLS_ASSERT(!ls_flist_init(&flist));
	ls_flist_add(&flist, TLS_DIR "lnk", 1, 0);
	ls_flist_start(&flist);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp(TLS_DIR "lnk, 0, 1\n"));
	TLS_ASSERT(!ls_flist_next(&flist, NULL));
	ls_flist_clear(&flist);
	TLS_ASSERT(tls_errcmp(""));
	TLS_STOP_FS;
}

TLS_TEST(test_files_nodirs)
{
	t_flist		flist;
	size_t		count;

	count = 0;
	count_config(&flist, &count);
	TLS_ASSERT(!ls_flist_init(&flist));
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCHT("197001010000.00", "dir");
	ls_flist_add(&flist, TLS_DIR "dir", 0, 1);
	ls_flist_start(&flist);
	TLS_ASSERT(ls_flist_print(&flist));
	TLS_ASSERT(tls_outcmp(TLS_DIR "dir, 0, 1\n"));
	TLS_ASSERT(!ls_flist_next(&flist, NULL));
	ls_flist_clear(&flist);
	TLS_ASSERT(tls_errcmp(""));
	TLS_STOP_FS;
}

void	test_files(void)
{
	ls_setprogname("ft_ls");
	TLS_RUN(test_files_traverse);
	TLS_RUN(test_files_reverse);
	TLS_RUN(test_files_recursive);
	TLS_RUN(test_files_nofollow);
	TLS_RUN(test_files_nodirs);
	TLS_RUN(test_files_errors);
}
