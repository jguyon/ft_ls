/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 22:16:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 20:07:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ls_tty.h"
#include "ls_callbacks.h"
#include "ft_memory.h"

static t_long_dinfo	g_long_info;

static t_cols_dinfo g_cols_info;

static void			config_sorting(t_flags *flags, t_flist *flist)
{
	if (flags->sorting == LS_SORT_SIZE)
		flist->compare = &ls_compare_size;
	else if (flags->sorting == LS_SORT_LEXI)
		flist->compare = &ls_compare_lexi;
	else if (flags->sorting == LS_SORT_TIME)
		flist->compare = &ls_compare_time;
	if (flags->time == LS_TIME_MODIF)
		g_get_time = &ls_get_mtime;
	else if (flags->time == LS_TIME_CHANGE)
		g_get_time = &ls_get_ctime;
	else if (flags->time == LS_TIME_ACCESS)
		g_get_time = &ls_get_atime;
}

static void			config_name(t_flags *flags)
{
	if (flags->color && ls_istty())
		g_print_name = &ls_name_color;
	else
		g_print_name = &ls_name_normal;
	if (flags->suffix == LS_SUFFIX_ALL)
		g_print_suffix = &ls_suffix_type;
	else if (flags->suffix == LS_SUFFIX_DIR)
		g_print_suffix = &ls_suffix_dir;
	else
		g_print_suffix = NULL;
}

static void			config_format(t_flags *flags, t_flist *flist)
{
	if (flags->format == LS_FORMAT_LONG)
	{
		flist->dirinfo = &g_long_info;
		flist->init = (t_flist_init *)&ls_init_long;
		flist->insert = (t_flist_insert *)&ls_insert_long;
		flist->print = (t_flist_print *)&ls_print_long;
	}
	else if (flags->format == LS_FORMAT_COLS)
	{
		flist->dirinfo = &g_cols_info;
		flist->init = (t_flist_init *)&ls_init_cols;
		flist->insert = (t_flist_insert *)&ls_insert_cols;
		flist->prepare = (t_flist_prepare *)&ls_prepare_cols;
		flist->print = (t_flist_print *)&ls_print_cols;
	}
	else if (flags->sorting == LS_SORT_TIME
			 || flags->sorting == LS_SORT_SIZE)
		flist->insert = &ls_insert_lstat;
	if (flags->show == LS_SHOW_NOHIDDEN)
		flist->reject = &ls_reject_hidden;
	else if (flags->show == LS_SHOW_ALMOST)
		flist->reject = &ls_reject_implied;
}

static void			config_flist(t_flags *flags, t_flist *flist)
{
	flist->reverse = flags->reverse;
	flist->recur = flags->recur && !(flags->nodirs);
	flist->error = &ls_file_error;
	flist->print = &ls_print_line;
	config_sorting(flags, flist);
	config_name(flags);
	config_format(flags, flist);
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
