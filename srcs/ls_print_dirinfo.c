/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_dirinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:40:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 17:24:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_format.h"
#include "ft_printf.h"

void	ls_print_dirinfo(t_flags flags, t_file *dir, t_dinfo *dinfo)
{
	ls_print_dir(dir->path ? dir->path : dir->name);
	if (flags.lfmt)
		ls_print_total(dinfo);
}
