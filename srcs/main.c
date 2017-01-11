/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:53:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 18:12:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_ls.h"
#include "ft_streams.h"

int		main(int argc, char **argv)
{
	t_args			args;
	t_dlist_node	*dirnode;
	t_file			*dir;

	ls_setprogname(argv[0]);
	if (!(ls_parse_args(argc, argv, &args)))
		ls_exit(LS_EXIT_FAILURE);
	if (ft_dlst_singular(&(args.dirs))
		&& ft_dlst_empty(&(args.files))
		&& (dirnode = ft_dlst_popl(&(args.dirs))))
	{
		dir = FT_DLST_ENTRY(&(args.dirs), dirnode);
		ls_list_files(args.flags, dir, &(args.files));
		ls_sort_files(args.flags, &(args.files));
		ls_print_files(args.flags, &(args.files));
		ls_destroy_file(dir);
		if (!ft_dlst_empty(&(args.files)))
			ft_dlst_joinl(&(args.dirs), &(args.files));
		if (!ft_dlst_empty(&(args.dirs)))
			ft_fputc('\n', FT_STDOUT);
	}
	else {
		ls_sort_files(args.flags, &(args.dirs));
		if (!ft_dlst_empty(&(args.files)))
		{
			ls_sort_files(args.flags, &(args.files));
			ls_print_files(args.flags, &(args.files));
			if (!ft_dlst_empty(&(args.files)))
				ft_dlst_joinl(&(args.dirs), &(args.files));
			if (!ft_dlst_empty(&(args.dirs)))
				ft_fputc('\n', FT_STDOUT);
		}
	}
	while ((dirnode = ft_dlst_popl(&(args.dirs))))
	{
		dir = FT_DLST_ENTRY(&(args.dirs), dirnode);
		ls_list_files(args.flags, dir, &(args.files));
		ls_sort_files(args.flags, &(args.files));
		ls_print_dirinfo(args.flags, dir);
		ls_print_files(args.flags, &(args.files));
		if (!ft_dlst_empty(&(args.files)))
			ft_dlst_joinl(&(args.dirs), &(args.files));
		if (!ft_dlst_empty(&(args.dirs)))
			ft_fputc('\n', FT_STDOUT);
		ls_destroy_file(dir);
	}
	return (ls_cleanup(LS_EXIT_SUCCESS));
}
