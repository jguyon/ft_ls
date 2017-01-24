/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 18:10:06 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 23:54:10 by jguyon           ###   ########.fr       */
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
	++(*count);
	return (0);
}

static int	count_print(size_t *count, t_file *file)
{
	(void)count;
	ft_fprintf(FT_STDOUT, "%s = %ld\n", file->name, (long)*((time_t *)file->info));
	return (0);
}

static int	count_compare(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f1->name, f2->name));
}

static int	count_reject(t_file *file)
{
	return (ft_strcmp(file->name, ".") == 0 || ft_strcmp(file->name, "..") == 0);
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
	TLS_TOUCHT("197001010000.01", "a/0");
	ls_flist_add(&flist, TLS_DIR "b", 1);
	ls_flist_add(&flist, TLS_DIR "a", 1);
	ls_flist_add(&flist, TLS_DIR "1", 1);
	ls_flist_add(&flist, TLS_DIR "0", 1);
	ls_flist_start(&flist);
	ls_flist_print(&flist);
	TLS_ASSERT(tls_outcmp(TLS_DIR "0 = 1\n" TLS_DIR "1 = 2\n"));
	TLS_ASSERT((next = ls_flist_next(&flist)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "a") == 0);
	ls_flist_print(&flist);
	TLS_ASSERT(tls_outcmp("0 = 1\n1 = 2\n3 = 4\n"));
	ls_file_del(&next);
	TLS_ASSERT((next = ls_flist_next(&flist)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "b") == 0);
	ls_flist_print(&flist);
	TLS_ASSERT(tls_outcmp(""));
	ls_file_del(&next);
	TLS_ASSERT(!ls_flist_next(&flist));
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
	ls_flist_add(&flist, TLS_DIR "none", 1);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "none: No such file or directory\n"));
	ls_flist_add(&flist, TLS_DIR "dir", 1);
	ls_flist_add(&flist, TLS_DIR "otherdir", 1);
	TLS_ASSERT(tls_errcmp(""));
	ls_flist_start(&flist);
	TLS_CHMOD("000", "dir");
	TLS_ASSERT((next = ls_flist_next(&flist)));
	TLS_ASSERT(next && strcmp(next->name, TLS_DIR "otherdir") == 0);
	ls_file_del(&next);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "dir: Permission denied\n"));
	ls_flist_clear(&flist);
	TLS_STOP_FS;
}

void	test_files(void)
{
	ls_setprogname("ft_ls");
	TLS_RUN(test_files_traverse);
	TLS_RUN(test_files_errors);
}
