/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/13 18:32:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_format.h"

TLS_TEST(test_format_mode)
{
	t_finfo		info;
	struct stat	st;

	bzero(&st, sizeof(st));
	st.st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX;
	ls_set_mode(&info, &st);
	printf("mode: %s\n", info.mode);
	TLS_ASSERT(strcmp(info.mode, "drwsrwsrwt") == 0);
}

void	test_format(void)
{
	TLS_RUN(test_format_mode);
}
