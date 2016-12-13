/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_destroy_nondirs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 01:51:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 20:36:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_ls.h"

TLS_TEST(test_destroy_nondirs_norec)
{
	unsigned int	flags;
	t_list			*files;
	t_ls_file		file;

	flags = 0;
	files = NULL;
	file.name = NULL;
	file.path = ft_strdup("..");
	file.info = NULL;
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFREG;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	file.path = ft_strdup("dir2");
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFDIR;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	file.path = ft_strdup("file1");
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFREG;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	file.path = ft_strdup("dir1");
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFDIR;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	ls_destroy_nondirs(flags, &files);
	TLS_ASSERT(files == NULL);
}

static t_ls_file	*file_at(t_list *files, size_t i)
{
	if (!files)
		return (NULL);
	if (i == 0)
		return (files->content);
	return (file_at(files->next, i - 1));
}

TLS_TEST(test_destroy_nondirs_rec)
{
	unsigned int	flags;
	t_list			*files;
	t_ls_file		file;
	t_ls_file		*tfile;

	flags = 0;
	LS_ADD_FLAG(flags, LS_FLAG_REC);
	files = NULL;
	file.path = NULL;
	file.name = ft_strdup("..");
	file.info = NULL;
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFDIR;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	file.name = ft_strdup("dir2");
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFDIR;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	file.name = ft_strdup("file1");
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFREG;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	file.name = ft_strdup("dir1");
	file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat)));
	file.stat->st_mode = S_IFDIR;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	ls_destroy_nondirs(flags, &files);
	TLS_ASSERT((tfile = file_at(files, 0)) && strcmp(tfile->name, "dir1") == 0);
	TLS_ASSERT((tfile = file_at(files, 1)) && strcmp(tfile->name, "dir2") == 0);
	TLS_ASSERT(!file_at(files, 2));
	ls_destroy_files(&files);
}

void	test_destroy_nondirs(void)
{
	TLS_RUN(test_destroy_nondirs_norec);
	TLS_RUN(test_destroy_nondirs_rec);
}
