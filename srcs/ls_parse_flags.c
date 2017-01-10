/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 20:44:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 21:16:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_program.h"
#include "ft_memory.h"

int		ls_parse_flags(int argc, char *const argv[], t_flags *flags)
{
	int		opt;

	ft_bzero(flags, sizeof(*flags));
	while ((opt = ls_getopt(argc, argv, LS_FLAGS)) != -1)
	{
		if (opt == LS_FLAG_ALL)
			flags->all = 1;
		else if (opt == LS_FLAG_LFMT)
			flags->lfmt = 1;
		else if (opt == LS_FLAG_MTIM)
			flags->mtim = 1;
		else if (opt == LS_FLAG_REV)
			flags->rev = 1;
		else if (opt == LS_FLAG_REC)
			flags->rec = 1;
		else if (opt == '?')
			return (0);
	}
	return (1);
}
