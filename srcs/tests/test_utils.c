/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 22:03:19 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/11 22:12:01 by jguyon           ###   ########.fr       */
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

void	test_utils(void)
{
	TLS_RUN(test_util_join_path);
}
