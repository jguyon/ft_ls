/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 00:03:44 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 00:32:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_ls.h"

static t_ls_file	*file_at(t_list *files, size_t i)
{
	if (!files)
		return (NULL);
	if (i == 0)
		return ((t_ls_file *)(files->content));
	return (file_at(files->next, i - 1));
}

TLS_TEST(test_list_files_normal)
{
	unsigned int	flags;
	t_list			*files;
	t_ls_file		*file;

	TLS_INIT_FS;
	TLS_MKDIR("normal");
	TLS_TOUCH("normal/folder");
	TLS_MKDIR("normal/dir");
	TLS_TOUCH("normal/file1");
	TLS_TOUCH("normal/file2");
	TLS_TOUCH("normal/Folder");
	flags = 0;
	files = ls_list_files(flags, TLS_DIR "normal");
	TLS_ASSERT(files);
	TLS_ASSERT((file = file_at(files, 0)) && strcmp(file->name, "Folder") == 0);
	TLS_ASSERT((file = file_at(files, 1)) && strcmp(file->name, "dir") == 0);
	TLS_ASSERT((file = file_at(files, 2)) && strcmp(file->name, "file1") == 0);
	TLS_ASSERT((file = file_at(files, 3)) && strcmp(file->name, "file2") == 0);
	TLS_ASSERT((file = file_at(files, 4)) && strcmp(file->name, "folder") == 0);
	TLS_ASSERT(!file_at(files, 5));
	ls_destroy_files(&files);
	TLS_STOP_FS;
}

TLS_TEST(test_list_files_error)
{
	unsigned int	flags;
	t_list			*files;

	tls_stmrst();
	TLS_INIT_FS;
	flags = 0;
	files = ls_list_files(flags, TLS_DIR "errorzzz");
	TLS_ASSERT(!files);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "errorzzz: No such file or directory\n"));
	ls_destroy_files(&files);
	TLS_STOP_FS;
}

void	test_list_files(void)
{
	TLS_RUN(test_list_files_normal);
	TLS_RUN(test_list_files_error);
}