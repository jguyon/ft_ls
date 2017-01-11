/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 10:53:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 01:59:01 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_ls.h"

int		main(int argc, char **argv)
{
	t_args	args;

	ls_setprogname(argv[0]);
	if (!(ls_parse_args(argc, argv, &args)))
		ls_exit(LS_EXIT_FAILURE);
	return (ls_cleanup(LS_EXIT_SUCCESS));
}
