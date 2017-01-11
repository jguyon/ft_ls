/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 21:08:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 12:35:00 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ft_ls.h"
#include "ls_program.h"
#include <stdlib.h>

static int	destroy_file(void *file, void *acc)
{
	(void)acc;
	ft_dlst_remove(&((t_file *)file)->node);
	free((void *)((t_file *)file)->path);
	free(file);
	return (1);
}

TLS_TEST(test_ls_parse_args)
{
	t_args		args;
	int			argc = 7;
	char		*argv[7] = {"ft_ls", "-aR", "-ltr",
							TLS_DIR "file", TLS_DIR "dir",
							TLS_DIR "link", TLS_DIR "none"};

	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCH("file");
	TLS_LNS("dir", "link");
	ls_setprogname("ft_ls");
	g_ls_optind = 1;
	TLS_ASSERT(ls_parse_args(argc, argv, &args));
	TLS_ASSERT(args.flags.all == 1);
	TLS_ASSERT(args.flags.lfmt == 1);
	TLS_ASSERT(args.flags.mtim == 1);
	TLS_ASSERT(args.flags.rev == 1);
	TLS_ASSERT(args.flags.rec == 1);
	TLS_ASSERT(tls_errcmp("ft_ls: " TLS_DIR "none: No such file or directory\n"));
	TLS_ASSERT(!ft_dlst_empty(&(args.dirs)) && !ft_dlst_singular(&(args.dirs)));
	TLS_ASSERT(ft_dlst_singular(&(args.files)));
	ft_dlst_foreachl(&(args.dirs), NULL, &destroy_file);
	ft_dlst_foreachl(&(args.files), NULL, &destroy_file);
	argc = 2;
	g_ls_optind = 1;
	TLS_ASSERT(ls_parse_args(argc, argv, &args));
	TLS_ASSERT(args.flags.all == 1);
	TLS_ASSERT(args.flags.lfmt == 0);
	TLS_ASSERT(args.flags.mtim == 0);
	TLS_ASSERT(args.flags.rev == 0);
	TLS_ASSERT(args.flags.rec == 1);
	TLS_ASSERT(tls_errcmp(""));
	TLS_ASSERT(ft_dlst_empty(&(args.dirs)));
	TLS_ASSERT(ft_dlst_empty(&(args.files)));
	g_ls_optind = 1;
	argv[1] = "-z";
	TLS_ASSERT(!ls_parse_args(argc, argv, &args));
	TLS_ASSERT(tls_errcmp("ft_ls: illegal option -- z\n"
				   "usage: ft_ls [-" LS_FLAGS "] [file ...]\n"));
	TLS_ASSERT(ft_dlst_empty(&(args.dirs)));
	TLS_ASSERT(ft_dlst_empty(&(args.files)));
	ls_setprogname(NULL);
	TLS_STOP_FS;
}

TLS_TEST(test_list_files)
{
	t_flags		flags;
	t_file		dir;
	t_dlist		files;

	bzero(&flags, sizeof(flags));
	bzero(&dir, sizeof(dir));
	dir.name = TLS_DIR "dir";
	TLS_INIT_FS;
	TLS_MKDIR("dir");
	TLS_TOUCH("dir/file");
	ls_list_files(flags, &dir, &files);
	TLS_ASSERT(tls_errcmp(""));
	TLS_ASSERT(ft_dlst_singular(&files));
	ft_dlst_foreachl(&files, NULL, &destroy_file);
	TLS_STOP_FS;
}

void	test_ls(void)
{
	TLS_RUN(test_ls_parse_args);
	TLS_RUN(test_list_files);
}
