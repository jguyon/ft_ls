/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:42:37 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 16:35:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_strings.h"
#include <stddef.h>

int		g_ls_optind = 1;

int		ls_getopt(int argc, char *const argv[], const char *optstring)
{
	static int			index = 0;
	static char	const	*next = NULL;

	if (index != g_ls_optind)
	{
		next = g_ls_optind > 0 && g_ls_optind < argc ? argv[g_ls_optind] : NULL;
		if (!next || next[0] != '-' || !next[1] || (next[1] == '-' && !next[2]))
		{
			if (next[1] == '-' && !next[2])
				++g_ls_optind;
			return (-1);
		}
		index = g_ls_optind;
		++next;
	}
	if (!ft_strchr(optstring, *next))
	{
		++g_ls_optind;
		ls_warnx("illegal option -- %c", *next);
		return ('?');
	}
	if (!(*(++next)))
		++g_ls_optind;
	return (*(next - 1));
}
