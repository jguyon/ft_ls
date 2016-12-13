/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:52 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 22:02:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	*print_dir(t_list *el, void *acc)
{
	t_ls_args	*args;
	t_list		*files;
	t_ls_file	*dir;
	t_ls_dinfo	*dinfo;

	dinfo = NULL;
	args = (t_ls_args *)acc;
	dir = (t_ls_file *)(el->content);
	if (el == args->dirs && !(args->files))
		ls_printf_out("%s: \n", dir->path);
	else
		ls_printf_out("\n%s:\n", dir->path);
	files = ls_list_files(args->flags, dir->path, &dinfo);
	if (dinfo)
		ls_printf_out("total %zu\n", dinfo->total);
	ls_print_files(args->flags, files, dinfo);
	ft_memdel((void **)&dinfo);
	ls_destroy_nondirs(args->flags, &files);
	if (files)
	{
		ft_lstfoldl(files, args, &print_dir);
		ls_destroy_files(&files);
	}
	return (args);
}

static void	print_first_dir(t_ls_args *args)
{
	t_list		*files;
	t_ls_file	*dir;
	t_ls_dinfo	*dinfo;

	dinfo = NULL;
	dir = (t_ls_file *)(args->dirs->content);
	files = ls_list_files(args->flags, dir->path, &dinfo);
	if (dinfo)
		ls_printf_out("total %zu\n", dinfo->total);
	ls_print_files(args->flags, files, dinfo);
	ft_memdel((void **)&dinfo);
	ls_destroy_nondirs(args->flags, &files);
	ft_lstfoldl(files, args, &print_dir);
	ls_destroy_files(&files);
}

int			main(int ac, char **av)
{
	t_ls_args	*args;

	ls_set_progname(av[0]);
	args = NULL;
	if (ls_open_streams() && (args = ls_parse_args(ac - 1, av + 1)))
	{
		if (!(args->files) && args->dirs && !(args->dirs->next))
			print_first_dir(args);
		else
		{
			ls_print_files(args->flags, args->files, NULL);
			ft_lstfoldl(args->dirs, args, &print_dir);
		}
	}
	ls_destroy_args(&args);
	ls_close_streams();
	return (0);
}
