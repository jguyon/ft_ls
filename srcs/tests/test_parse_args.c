/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:42:18 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 17:39:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests/test_ls.h"

TLS_TEST(test_args_cmd)
{
	char		*av[] = {"./ft_ls"};
	int			ac = 1;
	t_ls_args	*args;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && strcmp(args->cmd, "./ft_ls") == 0);
	TLS_ASSERT(args && args->files == NULL);
	free(args);
}

TLS_TEST(test_args_files)
{
	char		*av[] = {"./ft_ls", "file1", "file2"};
	int			ac = 3;
	t_ls_args	*args;
	char		*str;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && strcmp(args->cmd, "./ft_ls") == 0);
	TLS_ASSERT(args && args->files != NULL);
	str = args && args->files ? (char *)(args->files->content) : NULL;
	TLS_ASSERT(str && strcmp(str, "file2") == 0);
	str = str && args->files->next ? (char *)(args->files->next->content) : NULL;
	TLS_ASSERT(str && strcmp(str, "file1") == 0);
	ft_lstdel(&(args->files), &ft_lstdelcnt);
	free(args);
}

void	test_parse_args(void)
{
	TLS_RUN(test_args_cmd);
	TLS_RUN(test_args_files);
}
