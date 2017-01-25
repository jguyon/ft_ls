/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 22:16:45 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 15:53:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ls_callbacks.h"
#include "ft_memory.h"
#include "ft_printf.h"

static void	config_flist(t_flags *flags, t_flist *flist)
{
	flist->reverse = flags->reverse;
	flist->recur = flags->recur;
	flist->error = &ls_file_error;
	if (flags->sorting == LS_SORT_TIME || flags->sorting == LS_SORT_SIZE)
		flist->insert = &ls_insert_lstat;
	flist->print = &ls_print_line;
	if (flags->sorting == LS_SORT_SIZE)
		flist->compare = &ls_compare_size;
	else if (flags->sorting == LS_SORT_LEXI)
		flist->compare = &ls_compare_lexi;
	else if (flags->sorting == LS_SORT_TIME && flags->time == LS_TIME_MODIF)
		flist->compare = &ls_compare_mtim;
	else if (flags->sorting == LS_SORT_TIME && flags->time == LS_TIME_CHANGE)
		flist->compare = &ls_compare_ctim;
	else if (flags->sorting == LS_SORT_TIME && flags->time == LS_TIME_ACCESS)
		flist->compare = &ls_compare_atim;
	if (flags->show == LS_SHOW_NOHIDDEN)
		flist->reject = &ls_reject_hidden;
}

void		ls_parse_files(int argc, char *const argv[],
						   t_flags *flags, t_flist *flist)
{
	ft_bzero(flist, sizeof(*flist));
	config_flist(flags, flist);
	if (ls_flist_init(flist))
		ls_err(LS_EXIT_FAILURE, "%s", "ls_flist_init");
	if (g_ls_optind == argc)
		ls_flist_add(flist, ".", 0);
	else
	{
		while (g_ls_optind < argc)
		{
			ls_flist_add(flist, argv[g_ls_optind], 0);
			++g_ls_optind;
		}
	}
	ls_flist_start(flist);
}
