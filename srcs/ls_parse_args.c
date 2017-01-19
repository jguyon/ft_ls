/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 22:16:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 14:27:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ls_format.h"
#include "ft_memory.h"
#include "ft_printf.h"
#include <errno.h>

static int	parse_flags(int argc, char *const argv[], t_args *args)
{
	int		opt;

	ft_bzero(&(args->flags), sizeof(args->flags));
	while ((opt = ls_getopt(argc, argv, LS_FLAGS)) != -1)
	{
		if (opt == LS_FLAG_ALL)
			args->flags.all = 1;
		else if (opt == LS_FLAG_LFMT)
			args->flags.lfmt = 1;
		else if (opt == LS_FLAG_MTIM)
			args->flags.mtim = 1;
		else if (opt == LS_FLAG_REV)
			args->flags.rev = 1;
		else if (opt == LS_FLAG_REC)
			args->flags.rec = 1;
		else if (opt == '?')
		{
			g_ls_status = LS_EXIT_FAILURE;
			ft_fprintf(FT_STDERR, LS_USAGE_FMT, ls_getprogname(), LS_FLAGS);
			return (0);
		}
	}
	return (1);
}

static int	is_dir(const char *name, t_flags flags, struct stat *st)
{
	struct stat	target;

	return (S_ISDIR(st->st_mode)
			|| (!(flags.lfmt) && S_ISLNK(st->st_mode)
				&& !stat(name, &target)
				&& S_ISDIR(target.st_mode)));
}

static void	parse_file(const char *name, t_args *args)
{
	t_file		*file;

	errno = 0;
	if (!(file = (t_file *)ft_memalloc(sizeof(*file)))
	|| !(file->name = name) || lstat(file->name, &(file->stat)))
	{
		g_ls_status = LS_EXIT_FAILURE;
		ls_warn("%s", name[0] ? name : "\"\"");
		ft_memdel((void **)&file);
	}
	else if (is_dir(file->name, args->flags, &(file->stat)))
	{
		file->is_dir = 1;
		ft_dlst_pushr(&(args->dirs), &(file->node));
	}
	else
	{
		if (args->flags.lfmt)
			ls_update_info(&(args->dinfo), &(file->stat));
		ft_dlst_pushr(&(args->files), &(file->node));
	}
	if (file && args->flags.lfmt && !(file->is_dir))
	{
		file->extended = ls_extended_chr(file->name);
		file->owner = ls_get_owner(file->stat.st_uid);
		file->group = ls_get_group(file->stat.st_gid);
	}
}

static char	*g_currdir = ".";

static void	parse_currdir(t_args *args)
{
	t_file		*file;

	errno = 0;
	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
	{
		g_ls_status = LS_EXIT_FAILURE;
		ls_warn("%s", g_currdir);
		return ;
	}
	file->name = g_currdir;
	ft_dlst_pushr(&(args->dirs), &(file->node));
}

int			ls_parse_args(int argc, char *const argv[], t_args *args)
{
	if (!parse_flags(argc, argv, args))
		return (0);
	args->single = g_ls_optind < argc - 1 ? 0 : 1;
	ft_bzero(&(args->dinfo), sizeof(args->dinfo));
	FT_DLST_INIT(&(args->dirs), t_file, node);
	FT_DLST_INIT(&(args->files), t_file, node);
	if (g_ls_optind == argc)
		parse_currdir(args);
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
