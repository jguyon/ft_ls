/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 21:08:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 12:19:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ft_ls.h"
#include "ls_program.h"
#include "ft_dlists.h"
#include <stdlib.h>

static int	destroy_file(void *file, void *acc)
{
	(void)acc;
	ft_dlst_remove(&((t_file *)file)->node);
	ls_destroy_file(file);
	return (1);
}

TLS_TEST(test_ls_parse_args)
{
	t_args		args;
	int			argc = 7;
	char		*argv[7] = {"ft_ls", "-aR", "-ltr",
							TLS_DIR "file", TLS_DIR "dir",
							TLS_DIR "none", TLS_DIR "link"};

	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCH("file");
	TLS_LNS("dir", "link");
	ls_setprogname("ft_ls");
	g_ls_optind = 1;
	TLS_ASSERT(ls_parse_args(argc, argv, &args));
	TLS_ASSERT(!args.single);
	TLS_ASSERT(args.flags.all);
	TLS_ASSERT(args.flags.format == LS_FORMAT_LONG);
	TLS_ASSERT(args.flags.sorting == LS_SORT_MTIME);
	TLS_ASSERT(args.flags.reverse);
	TLS_ASSERT(args.flags.recur);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "none: No such file or directory\n"));
	TLS_ASSERT(ft_dlst_singular(&(args.dirs)));
	TLS_ASSERT(!ft_dlst_empty(&(args.files)) && !ft_dlst_singular(&(args.files)));
	ft_dlst_foreachl(&(args.dirs), NULL, &destroy_file);
	ft_dlst_foreachl(&(args.files), NULL, &destroy_file);
	argc = 2;
	g_ls_optind = 1;
	TLS_ASSERT(ls_parse_args(argc, argv, &args));
	TLS_ASSERT(args.single);
	TLS_ASSERT(args.flags.all);
	TLS_ASSERT(args.flags.format == LS_FORMAT_LINE);
	TLS_ASSERT(args.flags.sorting == LS_SORT_LEXI);
	TLS_ASSERT(!args.flags.reverse);
	TLS_ASSERT(args.flags.recur);
	TLS_ASSERT(tls_errcmp(""));
	TLS_ASSERT(ft_dlst_singular(&(args.dirs)));
	TLS_ASSERT(ft_dlst_empty(&(args.files)));
	ft_dlst_foreachl(&(args.dirs), NULL, &destroy_file);
	ft_dlst_foreachl(&(args.files), NULL, &destroy_file);
	g_ls_optind = 1;
	argv[1] = "-z";
	TLS_ASSERT(!ls_parse_args(argc, argv, &args));
	TLS_ASSERT(tls_errcmp("ft_ls: illegal option -- z\n"
				   "usage: ft_ls [-" LS_FLAGS "] [file ...]\n"));
	TLS_ASSERT(ft_dlst_empty(&(args.dirs)));
	TLS_ASSERT(ft_dlst_empty(&(args.files)));
	ft_dlst_foreachl(&(args.dirs), NULL, &destroy_file);
	ft_dlst_foreachl(&(args.files), NULL, &destroy_file);
	ls_setprogname(NULL);
	TLS_STOP_FS;
}

TLS_TEST(test_list_files)
{
	t_flags		flags;
	t_file		dir;
	t_dlist		files;
	t_dinfo		dinfo;

	bzero(&flags, sizeof(flags));
	bzero(&dir, sizeof(dir));
	dir.name = TLS_DIR "dir";
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCH("dir/file");
	ls_list_files(flags, &dir, &dinfo, &files);
	TLS_ASSERT(tls_errcmp(""));
	TLS_ASSERT(ft_dlst_singular(&files));
	ft_dlst_foreachl(&files, NULL, &destroy_file);
	TLS_STOP_FS;
}

TLS_TEST(test_print_files)
{
	t_flags		flags;
	t_file		dir;
	t_dlist		files;
	t_dlist		dirs;
	t_dinfo		dinfo;

	FT_DLST_INIT(&dirs, t_file, node);
	bzero(&flags, sizeof(flags));
	flags.recur = LS_BOOL_TRUE;
	bzero(&dir, sizeof(dir));
	dir.name = TLS_DIR "dir";
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCH("dir/file");
	TLS_MKDIR("dir/recdir");
	ls_list_files(flags, &dir, &dinfo, &files);
	ls_sort_files(flags, &files);
	TLS_ASSERT(!ft_dlst_empty(&files) && !ft_dlst_singular(&files));
	TLS_ASSERT(tls_errcmp(""));
	ls_print_dirinfo(0, flags, &dir, &dinfo);
	ls_print_files(flags, &files, &dinfo, &dirs);
	TLS_ASSERT(tls_outcmp(TLS_DIR "dir:\nfile\nrecdir\n\n"));
	TLS_ASSERT(ft_dlst_singular(&dirs)
			   && strcmp(((t_file *)FT_DLST_ENTRY(&dirs, ft_dlst_first(&dirs)))->name,
				 "recdir") == 0);
	ft_dlst_foreachl(&dirs, NULL, &destroy_file);
	TLS_STOP_FS;
}

TLS_TEST(test_sort_files)
{
	t_flags			flags;
	t_file			dir;
	t_dlist			files;
	t_dlist_node	*node;
	t_dinfo			dinfo;

	bzero(&flags, sizeof(flags));
	bzero(&dir, sizeof(dir));
	dir.name = TLS_DIR "dir";
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCHT("06060000", "dir/file1");
	TLS_TOUCHT("06060100", "dir/file2");
	ls_list_files(flags, &dir, &dinfo, &files);
	TLS_ASSERT(!ft_dlst_empty(&files) && !ft_dlst_singular(&files));
	TLS_ASSERT(tls_errcmp(""));
	ls_sort_files(flags, &files);
	TLS_ASSERT((node = ft_dlst_first(&files))
			   && strcmp(((t_file *)FT_DLST_ENTRY(&files, node))->name, "file1") == 0
			   && (node = ft_dlst_next(&files, node))
			   && strcmp(((t_file *)FT_DLST_ENTRY(&files, node))->name, "file2") == 0);
	ft_dlst_foreachl(&files, NULL, &destroy_file);
	flags.sorting = LS_SORT_MTIME;
	ls_list_files(flags, &dir, &dinfo, &files);
	TLS_ASSERT(!ft_dlst_empty(&files) && !ft_dlst_singular(&files));
	TLS_ASSERT(tls_errcmp(""));
	ls_sort_files(flags, &files);
	TLS_ASSERT((node = ft_dlst_first(&files))
			   && strcmp(((t_file *)FT_DLST_ENTRY(&files, node))->name, "file2") == 0
			   && (node = ft_dlst_next(&files, node))
			   && strcmp(((t_file *)FT_DLST_ENTRY(&files, node))->name, "file1") == 0);
	ft_dlst_foreachl(&files, NULL, &destroy_file);
	TLS_STOP_FS;
}

void	test_ls(void)
{
	TLS_RUN(test_ls_parse_args);
	TLS_RUN(test_list_files);
	TLS_RUN(test_print_files);
	TLS_RUN(test_sort_files);
}
