/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 22:16:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 16:11:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ls_format.h"
#include "ft_memory.h"
#include "ft_printf.h"
#include <errno.h>

static int	parse_one_flag(int opt, t_args *args)
{
	if (opt == '?')
		return (0);
	if (opt == LS_FLAG_ALL)
		args->flags.all = LS_BOOL_TRUE;
	else if (opt == LS_FLAG_LFMT)
		args->flags.format = LS_FORMAT_LONG;
	else if (opt == LS_FLAG_TIME)
		args->flags.sorting = LS_SORT_TIME;
	else if (opt == LS_FLAG_NOSRT)
	{
		args->flags.sorting = LS_SORT_NONE;
		args->flags.all = LS_BOOL_TRUE;
	}
	else if (opt == LS_FLAG_REV)
		args->flags.reverse = LS_BOOL_TRUE;
	else if (opt == LS_FLAG_REC)
		args->flags.recur = LS_BOOL_TRUE;
	else if (opt == LS_FLAG_LINE)
		args->flags.format = LS_FORMAT_LINE;
	else if (opt == LS_FLAG_ATIM)
		args->flags.time = LS_TIME_ACCESS;
	else if (opt == LS_FLAG_CTIM)
		args->flags.time = LS_TIME_CHANGE;
	return (1);
}

static int	parse_flags(int argc, char *const argv[], t_args *args)
{
	int		opt;

	ft_bzero(&(args->flags), sizeof(args->flags));
	while ((opt = ls_getopt(argc, argv, LS_FLAGS)) != -1)
	{
		if (!parse_one_flag(opt, args))
		{
			g_ls_status = LS_EXIT_FAILURE;
			ft_fprintf(FT_STDERR, LS_USAGE_FMT, ls_getprogname(), LS_FLAGS);
			return (0);
		}
	}
	return (1);
}

static int	is_dir(t_flags flags, t_file *file)
{
	struct stat	target;

	if (flags.format == LS_FORMAT_LONG || !S_ISLNK(file->stat->st_mode))
		return (file->is_dir);
	if (!stat(file->name, &target))
		return (S_ISDIR(target.st_mode));
	return (0);
}

static void	parse_file(const char *name, t_args *args)
{
	t_file		*file;

	errno = 0;
	if (!(file = ls_file_new(args->flags, name, NULL, 1)))
	{
		g_ls_status = LS_EXIT_FAILURE;
		ls_warn("%s", name[0] ? name : "\"\"");
		ft_memdel((void **)&file);
		return ;
	}
	if (is_dir(args->flags, file))
	{
		file->is_dir = 1;
		ft_dlst_pushr(&(args->dirs), &(file->node));
	}
	else
	{
		if (args->flags.format == LS_FORMAT_LONG)
			ls_update_dinfo(&(args->dinfo), file->info);
		ft_dlst_pushr(&(args->files), &(file->node));
	}
}

static char	*g_currdir = ".";

int			ls_parse_args(int argc, char *const argv[], t_args *args)
{
	if (!parse_flags(argc, argv, args))
		return (0);
	args->single = g_ls_optind < argc - 1 ? 0 : 1;
	ft_bzero(&(args->dinfo), sizeof(args->dinfo));
	FT_DLST_INIT(&(args->dirs), t_file, node);
	FT_DLST_INIT(&(args->files), t_file, node);
	if (g_ls_optind == argc)
		parse_file(g_currdir, args);
	else
	{
		while (g_ls_optind < argc)
		{
			parse_file(argv[g_ls_optind], args);
			++g_ls_optind;
		}
		if (!(ft_dlst_empty(&(args->files))))
			args->single = 0;
	}
	return (1);
}
