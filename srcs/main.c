/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:53:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 16:55:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_ls.h"
#include "ls_format.h"
#include "ft_streams.h"

static void	close_streams(void)
{
	ft_fclose(FT_STDOUT);
	ft_fclose(FT_STDERR);
}

static void	clear_caches(void)
{
	ls_cache_clear(&g_ls_owners);
	ls_cache_clear(&g_ls_groups);
}

int			main(int argc, char **argv)
{
	t_args			args;
	t_file			*dir;

	ls_setprogname(argv[0]);
	ls_atexit(&close_streams);
	ls_atexit(&clear_caches);
	if (!(ls_parse_args(argc, argv, &args)))
		ls_exit(LS_EXIT_STATUS);
	if (ft_dlst_singular(&(args.dirs))
		&& ft_dlst_empty(&(args.files))
		&& (dir = ls_pop_next(args.flags, &(args.dirs))))
	{
		ls_list_files(args.flags, dir, &(args.files));
		ls_sort_files(args.flags, &(args.files));
		ls_print_files(args.flags, &(args.files), &(args.dirs));
		ls_destroy_file(dir);
	}
	else
	{
		ls_sort_files(args.flags, &(args.dirs));
		if (!ft_dlst_empty(&(args.files)))
		{
			ls_sort_files(args.flags, &(args.files));
			ls_print_files(args.flags, &(args.files), &(args.dirs));
		}
	}
	while ((dir = ls_pop_next(args.flags, &(args.dirs))))
	{
		ls_list_files(args.flags, dir, &(args.files));
		ls_sort_files(args.flags, &(args.files));
		ls_print_dirinfo(args.flags, dir);
		ls_print_files(args.flags, &(args.files), &(args.dirs));
		ls_destroy_file(dir);
	}
	return (ls_cleanup(LS_EXIT_STATUS));
}
