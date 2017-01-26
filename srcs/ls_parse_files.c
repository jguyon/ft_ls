/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 22:16:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 13:19:32 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ls_tty.h"
#include "ls_callbacks.h"
#include "ft_memory.h"

static t_long_dinfo	g_long_info;

static void			config_flist(t_flags *flags, t_flist *flist)
{
	flist->reverse = flags->reverse;
	flist->recur = flags->recur && !(flags->nodirs);
	flist->error = &ls_file_error;
	flist->print = &ls_print_line;
	if (flags->format == LS_FORMAT_LONG)
	{
		flist->dirinfo = &g_long_info;
		flist->init = (t_flist_init *)&ls_init_long;
		flist->insert = (t_flist_insert *)&ls_insert_long;
		flist->print = (t_flist_print *)&ls_print_long;
	}
	else if (flags->sorting == LS_SORT_TIME || flags->sorting == LS_SORT_SIZE)
		flist->insert = &ls_insert_lstat;
	if (flags->sorting == LS_SORT_SIZE)
		flist->compare = &ls_compare_size;
	else if (flags->sorting == LS_SORT_LEXI)
		flist->compare = &ls_compare_lexi;
	else if (flags->sorting == LS_SORT_TIME)
		flist->compare = &ls_compare_time;
	if (flags->show == LS_SHOW_NOHIDDEN)
		flist->reject = &ls_reject_hidden;
	else if (flags->show == LS_SHOW_ALMOST)
		flist->reject = &ls_reject_implied;
	if (flags->time == LS_TIME_MODIF)
		g_get_time = &ls_get_mtime;
	else if (flags->time == LS_TIME_CHANGE)
		g_get_time = &ls_get_ctime;
	else if (flags->time == LS_TIME_ACCESS)
		g_get_time = &ls_get_atime;
	if (flags->color && ls_istty())
		g_print_name = &ls_name_color;
	else
		g_print_name = &ls_name_normal;
}

void				ls_parse_files(int argc, char *const argv[],
								   t_flags *flags, t_flist *flist)
{
	ft_bzero(flist, sizeof(*flist));
	config_flist(flags, flist);
	if (ls_flist_init(flist))
		ls_err(LS_EXIT_FAILURE, "%s", "ls_flist_init");
	if (g_ls_optind == argc)
		ls_flist_add(flist, ".", 0, flags->nodirs);
	else
	{
		while (g_ls_optind < argc)
		{
			ls_flist_add(flist, argv[g_ls_optind],
							flags->format == LS_FORMAT_LONG, flags->nodirs);
			++g_ls_optind;
		}
	}
	ls_flist_start(flist);
}
