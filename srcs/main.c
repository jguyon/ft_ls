/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:52 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/31 13:09:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_total(size_t total)
{
	char	*str;

	if (!(str = ft_uimtoa_base(total, 10, 0, 0)))
		return ;
	ls_puts_out("total ");
	ls_puts_out(str);
	ls_putc_out('\n');
}

static void	*print_dir(t_list *el, void *acc)
{
	t_ls_args	*args;
	t_list		*files;
	t_ls_file	*dir;
	t_ls_dinfo	*dinfo;

	dinfo = NULL;
	args = (t_ls_args *)acc;
	dir = (t_ls_file *)(el->content);
	if (el != args->dirs || args->files)
		ls_putc_out('\n');
	ls_puts_out(dir->path);
	ls_puts_out(":\n");
	files = ls_list_files(args->flags, dir->path, &dinfo);
	if (dinfo)
		print_total(dinfo->total);
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
		print_total(dinfo->total);
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
		if (!(args->files) && args->dirs && args->dir_count == 1)
			print_first_dir(args);
		else
		{
			ls_print_files(args->flags, args->files, args->dinfo);
			ft_lstfoldl(args->dirs, args, &print_dir);
		}
	}
	ls_destroy_args(&args);
	ls_close_streams();
	return (g_ls_status);
}
