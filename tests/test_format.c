/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:09:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/13 21:24:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_ls.h"
#include "ls_format.h"

TLS_TEST(test_format_mode)
{
	t_finfo		info;
	struct stat	st;

	st.st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO | S_ISUID | S_ISGID | S_ISVTX;
	ls_set_mode(&info, &st);
	TLS_ASSERT(strcmp(info.mode, "drwsrwsrwt") == 0);
}

TLS_TEST(test_format_nlinks)
{
	t_finfo		info;
	struct stat	st;

	st.st_nlink = 132;
	TLS_ASSERT(ls_set_nlinks(&info, &st) == 3);
	TLS_ASSERT(strcmp(info.nlinks, "132") == 0);
}

void	test_format(void)
{
	TLS_RUN(test_format_mode);
	TLS_RUN(test_format_nlinks);
}
