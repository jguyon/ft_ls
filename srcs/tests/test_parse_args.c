/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parse_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:42:18 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 21:18:22 by jguyon           ###   ########.fr       */
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
	TLS_ASSERT(args && args->flags == 0);
	TLS_ASSERT(args && args->files == NULL);
	ls_destroy_args(&args);
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
	TLS_ASSERT(args && args->flags == 0);
	TLS_ASSERT(args && args->files != NULL);
	str = args && args->files ? (char *)(args->files->content) : NULL;
	TLS_ASSERT(str && strcmp(str, "file2") == 0);
	str = str && args->files->next ? (char *)(args->files->next->content) : NULL;
	TLS_ASSERT(str && strcmp(str, "file1") == 0);
	ls_destroy_args(&args);
}

TLS_TEST(test_args_all_flags)
{
	char		*av[] = {"./ft_ls", "-lRart"};
	int			ac = 2;
	t_ls_args	*args;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && strcmp(args->cmd, "./ft_ls") == 0);
	TLS_ASSERT(args && args->files == NULL);
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_LNG));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_REC));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_ALL));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_REV));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_TME));
	ls_destroy_args(&args);
}

TLS_TEST(test_args_some_flags)
{
	char		*av[] = {"./ft_ls", "-l", "-t", "-a"};
	int			ac = 4;
	t_ls_args	*args;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && strcmp(args->cmd, "./ft_ls") == 0);
	TLS_ASSERT(args && args->files == NULL);
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_LNG));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REC));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_ALL));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REV));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_TME));
	ls_destroy_args(&args);
}

TLS_TEST(test_args_invalid_flag)
{
	char		*av[] = {"./ft_ls", "-l", "-tz"};
	int			ac = 3;
	t_ls_args	*args;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args == NULL);
	ls_destroy_args(&args);
}

TLS_TEST(test_args_empty_flag)
{
	char		*av[] = {"./ft_ls", "-a", "-"};
	int			ac = 3;
	t_ls_args	*args;
	char		*str;

	args = ls_parse_args(ac, av);
	TLS_ASSERT(args != NULL);
	TLS_ASSERT(args && strcmp(args->cmd, "./ft_ls") == 0);
	str = args && args->files ? (char *)(args->files->content) : NULL;
	TLS_ASSERT(str && strcmp(str, "-") == 0);
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_LNG));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REC));
	TLS_ASSERT(args && LS_HAS_FLAG(args->flags, LS_FLAG_ALL));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_REV));
	TLS_ASSERT(args && !LS_HAS_FLAG(args->flags, LS_FLAG_TME));
	ls_destroy_args(&args);
}

void	test_parse_args(void)
{
	TLS_RUN(test_args_cmd);
	TLS_RUN(test_args_files);
	TLS_RUN(test_args_all_flags);
	TLS_RUN(test_args_some_flags);
	TLS_RUN(test_args_invalid_flag);
	TLS_RUN(test_args_empty_flag);
}
