/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:42:18 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 19:57:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_ls.h"

static t_ls_file	*file_at(t_list *files, size_t i)
{
	if (!files)
		return (NULL);
	if (i == 0)
		return (files->content);
	return (file_at(files->next, i - 1));
}

TLS_TEST(test_args_files)
{
	char		*av[] = {TLS_DIR "file2", TLS_DIR "dir1", TLS_DIR "file1", TLS_DIR "dir1/file3"};
	int			ac = 4;
	t_ls_args	*args;
	t_ls_file	*file;

	TLS_INIT_FS;
	TLS_MKDIR("dir1");
	TLS_TOUCH("file2");
	TLS_TOUCH("file1");
	TLS_TOUCH("dir1/file3");
	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && args->flags == 0);
	file = args ? file_at(args->files, 0) : NULL;
	TLS_ASSERT(file && strcmp(file->path, TLS_DIR "dir1/file3") == 0);
	file = args ? file_at(args->files, 1) : NULL;
	TLS_ASSERT(file && strcmp(file->path, TLS_DIR "file1") == 0);
	file = args ? file_at(args->files, 2) : NULL;
	TLS_ASSERT(file && strcmp(file->path, TLS_DIR "file2") == 0);
	TLS_ASSERT(args && !file_at(args->files, 4));
	file = args ? file_at(args->dirs, 0) : NULL;
	TLS_ASSERT(file && strcmp(file->path, TLS_DIR "dir1") == 0);
	TLS_ASSERT(args && !file_at(args->dirs, 1));
	ls_destroy_args(&args);
	TLS_STOP_FS;
}

TLS_TEST(test_args_all_flags)
{
	char		*av[] = {"-lRart"};
	int			ac = 1;
	t_ls_args	*args;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && args->files == NULL && args->dirs == NULL);
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_LNG));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_REC));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_ALL));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_REV));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_TME));
	ls_destroy_args(&args);
}

TLS_TEST(test_args_some_flags)
{
	char		*av[] = {"-l", "-t", "-a"};
	int			ac = 3;
	t_ls_args	*args;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && args->files == NULL && args->dirs == NULL);
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_LNG));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REC));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_ALL));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REV));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_TME));
	ls_destroy_args(&args);
}

TLS_TEST(test_args_invalid_flag)
{
	char		*av[] = {"-l", "-tz"};
	int			ac = 2;
	t_ls_args	*args;

	tls_stmrst();
	args = ls_parse_args(ac, av);
	TLS_ASSERT(args == NULL);
	TLS_ASSERT(tls_errcmp("ft_ls: illegal option -- z\nusage: ft_ls [-lRart] [file ...]\n"));
	ls_destroy_args(&args);
}

TLS_TEST(test_args_empty_flag)
{
	char		*av[] = {"-a", "-"};
	int			ac = 2;
	t_ls_args	*args;

	tls_stmrst();
	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && args->files == NULL && args->dirs == NULL);
	TLS_ASSERT(tls_errcmp("ft_ls: -: No such file or directory\n"));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_LNG));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REC));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_ALL));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REV));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_TME));
	ls_destroy_args(&args);
}

void	test_parse_args(void)
{
	TLS_RUN(test_args_files);
	TLS_RUN(test_args_all_flags);
	TLS_RUN(test_args_some_flags);
	TLS_RUN(test_args_invalid_flag);
	TLS_RUN(test_args_empty_flag);
}
