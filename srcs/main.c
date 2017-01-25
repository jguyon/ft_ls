/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:53:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 17:02:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ft_streams.h"

static void		close_streams(void)
{
	ft_fclose(FT_STDOUT);
	ft_fclose(FT_STDERR);
}

static t_flags	g_flags;

static t_flist	g_flist;

static void		cleanup_files(void)
{
	ls_cleanup_files(&g_flist);
}

int				main(int argc, char **argv)
{
	ls_setprogname(argv[0]);
	ls_atexit(&close_streams);
	if (ls_parse_flags(argc, argv, &g_flags))
		return (ls_cleanup(LS_EXIT_FAILURE));
	ls_parse_files(argc, argv, &g_flags, &g_flist);
	ls_atexit(&cleanup_files);
	return (ls_cleanup(ls_print_files(&g_flags, &g_flist)));
}
