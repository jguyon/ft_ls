/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:53:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 20:31:17 by jguyon           ###   ########.fr       */
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

static void	print_files(t_args *args)
{
	ls_sort_files(args->flags, &(args->dirs));
	if (!ft_dlst_empty(&(args->files)))
	{
		ls_sort_files(args->flags, &(args->files));
		ls_print_files(args->flags, &(args->files),
						&(args->dinfo), &(args->dirs));
	}
}

static int	print_next(int is_single, t_args *args)
{
	t_file	*dir;

	if (!(dir = ls_pop_next(args->flags, &(args->dirs))))
		return (0);
	ls_list_files(args->flags, dir, &(args->dinfo), &(args->files));
	ls_sort_files(args->flags, &(args->files));
	ls_print_dirinfo(is_single, args->flags, dir, &(args->dinfo));
	ls_print_files(args->flags, &(args->files), &(args->dinfo), &(args->dirs));
	ls_destroy_file(dir);
	return (1);
}

int			main(int argc, char **argv)
{
	t_args	args;

	ls_setprogname(argv[0]);
	ls_atexit(&close_streams);
	ls_atexit(&clear_caches);
	if (!(ls_parse_args(argc, argv, &args)))
		ls_exit(LS_EXIT_STATUS);
	if (ft_dlst_singular(&(args.dirs)) && ft_dlst_empty(&(args.files)))
		print_next(1, &args);
	else
		print_files(&args);
	while (print_next(0, &args))
		;
	return (ls_cleanup(LS_EXIT_STATUS));
}
