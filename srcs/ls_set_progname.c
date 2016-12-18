/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_progname.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 23:22:24 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/18 14:03:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_set_progname(char *name)
{
	char	*prog;

	if (name && (prog = ft_strrchr(name, '/')))
		g_ls_progname = prog + 1;
}
