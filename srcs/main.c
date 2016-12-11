/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:52 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 00:38:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_ls_args	*args;
	t_list		*files;

	ls_set_progname(av[0]);
	args = NULL;
	if (ls_open_streams() && (args = ls_parse_args(ac - 1, av + 1)))
	{
		if (!(args->files) || !(args->files->next))
		{
			files = args->files
				? ls_list_files(args->flags, (char *)(args->files->content))
				: ls_list_files(args->flags, ".");
			ls_print_files(args->flags, files);
			ls_destroy_files(&files);
		}
		else
			ls_printf_err(0, "Not implemented yet");
	}
	ls_destroy_args(&args);
	ls_close_streams();
	return (0);
}
