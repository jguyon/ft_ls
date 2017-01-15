/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 20:50:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_format.h"
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

TLS_TEST(test_format_dinfo)
{
	t_dinfo		info;
	struct stat	st;

	bzero(&info, sizeof(info));
	st.st_mode = S_IFBLK;
	st.st_blocks = 512;
	st.st_nlink = 16;
	st.st_uid = getuid();
	st.st_gid = getgid();
	st.st_dev = makedev(13, 3);
	ls_update_info(&info, &st);
	TLS_ASSERT(info.total == 512);
	TLS_ASSERT(info.max_nlink == 2);
	TLS_ASSERT(info.max_owner == strlen(getpwuid(st.st_uid)->pw_name));
	TLS_ASSERT(info.max_group == strlen(getgrgid(st.st_gid)->gr_name));
	TLS_ASSERT(info.max_size == 0);
	TLS_ASSERT(info.max_maj == 2);
	TLS_ASSERT(info.max_min == 1);
	ls_cache_clear(&g_ls_owners);
	ls_cache_clear(&g_ls_groups);
}

void	test_format(void)
{
	TLS_RUN(test_format_dinfo);
}
