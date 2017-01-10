/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_setprogname.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:27:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 11:38:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_strings.h"

const char	*g_ls_progname = NULL;

void		ls_setprogname(const char *name)
{
	const char	*last;

	if (name && (last = ft_strrchr(name, '/')))
		g_ls_progname = last + 1;
	else
		g_ls_progname = name;
}
