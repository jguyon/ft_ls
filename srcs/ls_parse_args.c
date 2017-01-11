/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 22:16:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 16:42:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ft_memory.h"
#include "ft_printf.h"

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
			ft_fprintf(FT_STDERR, LS_USAGE_FMT, ls_getprogname(), LS_FLAGS);
			return (0);
		}
	}
	return (1);
}

static int	is_dir(const char *name, struct stat *st)
{
	struct stat	target;

	return (S_ISDIR(st->st_mode)
			|| (S_ISLNK(st->st_mode)
				&& !stat(name, &target)
				&& S_ISDIR(target.st_mode)));
}

static int	parse_file(int argc, char *const argv[], t_args *args)
{
	t_file		*file;

	if (g_ls_optind >= argc)
		return (0);
	if (!(file = (t_file *)ft_memalloc(sizeof(*file)))
		|| !(file->name = argv[g_ls_optind])
		|| lstat(file->name, &(file->stat)))
	{
		ls_warn("%s", argv[g_ls_optind]);
		ft_memdel((void **)&file);
		++g_ls_optind;
		return (1);
	}
	++g_ls_optind;
	if (is_dir(file->name, &(file->stat)))
	{
		file->is_dir = 1;
		ft_dlst_pushr(&(args->dirs), &(file->node));
	}
	else
		ft_dlst_pushr(&(args->files), &(file->node));
	return (1);
}

static char	*g_currdir = ".";

static void	parse_currdir(t_args *args)
{
	t_file		*file;

	if (!(file = (t_file *)ft_memalloc(sizeof(*file))))
	{
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
	FT_DLST_INIT(&(args->dirs), t_file, node);
	FT_DLST_INIT(&(args->files), t_file, node);
	if (g_ls_optind == argc)
		parse_currdir(args);
	else
	{
		while (parse_file(argc, argv, args))
			;
	}
	return (1);
}
