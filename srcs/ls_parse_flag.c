/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 18:42:08 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 18:47:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	if (opt == LS_FLAG_LFMT || opt == LS_FLAG_USR || opt == LS_FLAG_GRP
		|| opt == LS_FLAG_NUM)
		flags->format = LS_FORMAT_LONG;
	if (opt == LS_FLAG_ACROSS)
		flags->format = LS_FORMAT_ACROSS;
	else if (opt == LS_FLAG_STREAM)
		flags->format = LS_FORMAT_STREAM;
	else if (opt == LS_FLAG_USR)
		flags->nogroup = LS_BOOL_TRUE;
	else if (opt == LS_FLAG_GRP)
		flags->noowner = LS_BOOL_TRUE;
	else if (opt == LS_FLAG_LINE)
		flags->format = LS_FORMAT_LINE;
	else if (opt == LS_FLAG_NUM)
		flags->numeric = LS_BOOL_TRUE;
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

void		ls_parse_flag(t_flags *flags, int opt)
{
	parse_traversing(flags, opt);
	parse_format(flags, opt);
	parse_sorting(flags, opt);
}
