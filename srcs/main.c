/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:52 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/11 14:10:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_ls_args	*args;

	ls_set_progname(av[0]);
	args = NULL;
	if (ls_open_streams() && (args = ls_parse_args(ac - 1, av + 1)))
		ls_printf_out("TODO\n");
	ls_destroy_args(&args);
	ls_close_streams();
	return (0);
}
