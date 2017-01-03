/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:46:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 16:46:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"

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
	t_ls_dinfo		*dinfo;

	TLS_INIT_FS;
	TLS_MKDIR("normal");
	TLS_TOUCH("normal/folder");
	TLS_MKDIR("normal/dir");
	TLS_MKDIR("normal/.hidden");
	TLS_TOUCH("normal/file1");
	TLS_TOUCH("normal/file2");
	TLS_MKDIR("normal/FolderReal");
	flags = 0;
	files = ls_list_files(flags, TLS_DIR "normal", &dinfo);
	TLS_ASSERT(files);
	TLS_ASSERT(dinfo == NULL);
	TLS_ASSERT((file = file_at(files, 0)) && strcmp(file->name, "FolderReal") == 0);
	TLS_ASSERT((file = file_at(files, 1)) && strcmp(file->name, "dir") == 0);
	TLS_ASSERT((file = file_at(files, 2)) && strcmp(file->name, "file1") == 0);
	TLS_ASSERT((file = file_at(files, 3)) && strcmp(file->name, "file2") == 0);
	TLS_ASSERT((file = file_at(files, 4)) && strcmp(file->name, "folder") == 0);
	TLS_ASSERT(!file_at(files, 5));
	ls_destroy_files(&files);
	TLS_STOP_FS;
}

TLS_TEST(test_list_files_hidden)
{
	unsigned int	flags;
	t_list			*files;
	t_ls_file		*file;
	t_ls_dinfo		*dinfo;

	TLS_INIT_FS;
	TLS_MKDIR("normal");
	TLS_TOUCH("normal/folder");
	TLS_MKDIR("normal/dir");
	TLS_MKDIR("normal/.hidden");
	TLS_TOUCH("normal/file1");
	TLS_TOUCH("normal/file2");
	TLS_TOUCH("normal/FolderReal");
	flags = 0;
	LS_ADD_FLAG(flags, LS_FLAG_ALL);
	files = ls_list_files(flags, TLS_DIR "normal", &dinfo);
	TLS_ASSERT(files);
	TLS_ASSERT(dinfo == NULL);
	TLS_ASSERT((file = file_at(files, 0)) && strcmp(file->name, ".") == 0);
	TLS_ASSERT((file = file_at(files, 1)) && strcmp(file->name, "..") == 0);
	TLS_ASSERT((file = file_at(files, 2)) && strcmp(file->name, ".hidden") == 0);
	TLS_ASSERT((file = file_at(files, 3)) && strcmp(file->name, "FolderReal") == 0);
	TLS_ASSERT((file = file_at(files, 4)) && strcmp(file->name, "dir") == 0);
	TLS_ASSERT((file = file_at(files, 5)) && strcmp(file->name, "file1") == 0);
	TLS_ASSERT((file = file_at(files, 6)) && strcmp(file->name, "file2") == 0);
	TLS_ASSERT((file = file_at(files, 7)) && strcmp(file->name, "folder") == 0);
	TLS_ASSERT(!file_at(files, 8));
	ls_destroy_files(&files);
	TLS_STOP_FS;
}

TLS_TEST(test_list_files_error)
{
	unsigned int	flags;
	t_list			*files;
	t_ls_dinfo		*dinfo;

	tls_stmrst();
	TLS_INIT_FS;
	flags = 0;
	files = ls_list_files(flags, TLS_DIR "errorzzz", &dinfo);
	TLS_ASSERT(!files);
	TLS_ASSERT(dinfo == NULL);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "errorzzz: No such file or directory\n"));
	ls_destroy_files(&files);
	TLS_STOP_FS;
}

void	test_list_files(void)
{
	TLS_RUN(test_list_files_normal);
	TLS_RUN(test_list_files_hidden);
	TLS_RUN(test_list_files_error);
}
