/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:50:17 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 16:50:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"

TLS_TEST(test_simple_print_files)
{
	t_ls_file		file;
	t_list			*files;
	unsigned int	flags;

	flags = 0;
	file.stat = NULL;
	file.path = ft_strdup("dir1/file1");
	file.name = ft_strdup("file1");
	file.info = NULL;
	files = NULL;
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	file.name = NULL;
	file.path = ft_strdup("dir2/file2");
	ft_lstadd(&files, ft_lstnew(&file, sizeof(file)));
	tls_stmrst();
	ls_print_files(flags, files, NULL);
	TLS_ASSERT(tls_outcmp("dir2/file2\nfile1\n"));
	ls_destroy_files(&files);
}

void	test_print_files(void)
{
	TLS_RUN(test_simple_print_files);
}
