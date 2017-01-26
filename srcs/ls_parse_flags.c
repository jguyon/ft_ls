/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 18:42:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 11:07:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ft_memory.h"
#include "ft_printf.h"

static void	parse_traversing(t_flags *flags, int opt)
{
	if (opt == LS_FLAG_ALL || opt == LS_FLAG_NOSRT)
		flags->show = LS_SHOW_ALL;
	else if (opt == LS_FLAG_ALMOST && flags->show != LS_SHOW_ALL)
		flags->show = LS_SHOW_ALMOST;
	else if (opt == LS_FLAG_REC)
		flags->recur = LS_BOOL_TRUE;
	else if (opt == LS_FLAG_NODIR)
		flags->nodirs = LS_BOOL_TRUE;
}

static void	parse_format(t_flags *flags, int opt)
{
	if (opt == LS_FLAG_LFMT)
		flags->format = LS_FORMAT_LONG;
	else if (opt == LS_FLAG_LINE)
		flags->format = LS_FORMAT_LINE;
}

static void	parse_sorting(t_flags *flags, int opt)
{
	if (opt == LS_FLAG_TIME && !(flags->sorting))
		flags->sorting = LS_SORT_TIME;
	else if (opt == LS_FLAG_SIZE)
		flags->sorting = LS_SORT_SIZE;
	else if (opt == LS_FLAG_NOSRT)
		flags->sorting = LS_SORT_NONE;
	else if (opt == LS_FLAG_REV)
		flags->reverse = LS_BOOL_TRUE;
	else if (opt == LS_FLAG_ATIM)
		flags->time = LS_TIME_ACCESS;
	else if (opt == LS_FLAG_CTIM)
		flags->time = LS_TIME_CHANGE;
}

int			ls_parse_flags(int argc, char *const argv[], t_flags *flags)
{
	int		opt;

	ft_bzero(flags, sizeof(*flags));
	while ((opt = ls_getopt(argc, argv, LS_FLAGS)) != -1)
	{
		if (opt == '?')
		{
			ft_fprintf(FT_STDERR, LS_USAGE_FMT, ls_getprogname(), LS_FLAGS);
			return (-1);
		}
		parse_traversing(flags, opt);
		parse_format(flags, opt);
		parse_sorting(flags, opt);
	}
	flags->singlearg = g_ls_optind < argc - 1 ? 0 : 1;
	return (0);
}
