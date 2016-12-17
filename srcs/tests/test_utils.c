/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 22:03:19 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/17 23:51:35 by jguyon           ###   ########.fr       */
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
	f.info = NULL;
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
	f.info = NULL;
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

TLS_TEST(test_util_file_mode_type)
{
	struct stat	sb;
	char		*str;

	sb.st_mode = 0 | S_IFSOCK;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("s---------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFLNK;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("l---------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("----------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFBLK;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("b---------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFDIR;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("d---------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFDIR;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("d---------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFCHR;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("c---------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFIFO;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("p---------", str) == 0);
	free(str);
}

TLS_TEST(test_util_file_mode_own)
{
	struct stat	sb;
	char		*str;

	sb.st_mode = 0 | S_IFREG;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("----------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IRUSR;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("-r--------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IWUSR;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("--w-------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IXUSR;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("---x------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISUID;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("---S------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISUID | S_IXUSR;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("---s------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISUID | S_IRWXU;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("-rws------", str) == 0);
	free(str);
}

TLS_TEST(test_util_file_mode_grp)
{
	struct stat	sb;
	char		*str;

	sb.st_mode = 0 | S_IFREG;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("----------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IRGRP;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("----r-----", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IWGRP;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("-----w----", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IXGRP;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("------x---", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISGID;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("------S---", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISGID | S_IXGRP;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("------s---", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISGID | S_IRWXG;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("----rws---", str) == 0);
	free(str);
}

TLS_TEST(test_util_file_mode_oth)
{
	struct stat	sb;
	char		*str;

	sb.st_mode = 0 | S_IFREG;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("----------", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IROTH;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("-------r--", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IWOTH;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("--------w-", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_IXOTH;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("---------x", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISVTX;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("---------T", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISVTX | S_IXOTH;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("---------t", str) == 0);
	free(str);
	sb.st_mode = 0 | S_IFREG | S_ISVTX | S_IRWXO;
	str = ls_file_mode(&sb);
	TLS_ASSERT(str && strcmp("-------rwt", str) == 0);
	free(str);
}

TLS_TEST(test_util_file_nlinks)
{
	struct stat	sb;
	char		*str;

	sb.st_nlink = 123;
	str = ls_file_nlinks(&sb);
	TLS_ASSERT(str && strcmp(str, "123") == 0);
	free(str);
}

TLS_TEST(test_util_file_owner)
{
	struct stat	sb;
	char		*str;

	sb.st_uid = 123456;
	str = ls_file_owner(&sb);
	TLS_ASSERT(str && strcmp(str, "123456") == 0);
	free(str);
	TLS_INIT_FS;
	TLS_TOUCH("file");
	lstat(TLS_DIR "file", &sb);
	str = ls_file_owner(&sb);
	TLS_ASSERT(str && strcmp(str, "123456"));
	free(str);
	TLS_STOP_FS;
}

TLS_TEST(test_util_file_group)
{
	struct stat	sb;
	char		*str;

	sb.st_gid = 123456;
	str = ls_file_group(&sb);
	TLS_ASSERT(str && strcmp(str, "123456") == 0);
	free(str);
	TLS_INIT_FS;
	TLS_TOUCH("file");
	lstat(TLS_DIR "file", &sb);
	str = ls_file_group(&sb);
	TLS_ASSERT(str && strcmp(str, "123456"));
	free(str);
	TLS_STOP_FS;
}

TLS_TEST(test_util_file_size)
{
	struct stat	sb;
	char		*str;

	sb.st_size = 42;
	str = ls_file_size(&sb);
	TLS_ASSERT(str && strcmp(str, "42") == 0);
	free(str);
}

TLS_TEST(test_util_file_devn)
{
	struct stat	sb;
	char		*maj;
	char		*min;

	sb.st_rdev = makedev(24, 42);
	sb.st_mode = 0 | S_IFBLK;
	TLS_ASSERT(ls_file_devn(&sb, &maj, &min));
	TLS_ASSERT(maj && strcmp(maj, "24") == 0);
	TLS_ASSERT(min && strcmp(min, "42") == 0);
	free(maj);
	free(min);
}

TLS_TEST(test_util_file_time)
{
	struct stat	sb;
	char		*str;
	char		exp[14] = {0};

	sb.st_mtime = time(NULL) - (365 * 24 * 3600);
	str = ls_file_time(&sb);
	strftime(exp, 14, "%b %e  %Y", localtime(&(sb.st_mtime)));
	TLS_ASSERT(str && strcmp(str, exp) == 0);
	free(str);
	sb.st_mtime = time(NULL) + (365 * 24 * 3600);
	str = ls_file_time(&sb);
	strftime(exp, 14, "%b %e  %Y", localtime(&(sb.st_mtime)));
	TLS_ASSERT(str && strcmp(str, exp) == 0);
	free(str);
	sb.st_mtime = time(NULL);
	str = ls_file_time(&sb);
	strftime(exp, 14, "%b %e %H:%M", localtime(&(sb.st_mtime)));
	TLS_ASSERT(str && strcmp(str, exp) == 0);
	free(str);
	sb.st_mtime = time(NULL) + (252288000000);
	str = ls_file_time(&sb);
	strftime(exp, 14, "%b %e  %Y", localtime(&(sb.st_mtime)));
	TLS_ASSERT(str && strcmp(str, exp) == 0);
	free(str);
}

TLS_TEST(test_util_file_link)
{
	char		*str;
	struct stat	sb;

	TLS_INIT_FS;
	TLS_TOUCH("file");
	TLS_LNS("file", "link");
	lstat(TLS_DIR "link", &sb);
	str = ls_file_link(TLS_DIR "link", &sb);
	TLS_ASSERT(str && strcmp(str, TLS_DIR "file") == 0);
	free(str);
	TLS_STOP_FS;
}

TLS_TEST(test_util_file_info)
{
	t_ls_finfo	*finfo;
	t_ls_dinfo	dinfo;
	struct stat	sb;

	ft_bzero(&dinfo, sizeof(dinfo));
	ft_bzero(&sb, sizeof(sb));
	sb.st_blocks = 365;
	finfo = ls_file_info("somefile", &sb, &dinfo);
	TLS_ASSERT(finfo != NULL);
	TLS_ASSERT(finfo && strcmp(finfo->size, "365"));
	TLS_ASSERT(dinfo.total == 365);
	ls_destroy_finfo(&finfo);
}

void	test_utils(void)
{
	TLS_RUN(test_util_join_path);
	TLS_RUN(test_util_lexi_cmp);
	TLS_RUN(test_util_lexi_revcmp);
	TLS_RUN(test_util_modt_cmp);
	TLS_RUN(test_util_modt_revcmp);
	TLS_RUN(test_util_sort_fun);
	TLS_RUN(test_util_file_mode_type);
	TLS_RUN(test_util_file_mode_own);
	TLS_RUN(test_util_file_mode_grp);
	TLS_RUN(test_util_file_mode_oth);
	TLS_RUN(test_util_file_nlinks);
	TLS_RUN(test_util_file_owner);
	TLS_RUN(test_util_file_group);
	TLS_RUN(test_util_file_size);
	TLS_RUN(test_util_file_devn);
	TLS_RUN(test_util_file_time);
	TLS_RUN(test_util_file_link);
	TLS_RUN(test_util_file_info);
}
