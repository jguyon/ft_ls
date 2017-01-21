/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_dirinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:40:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/21 12:15:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_format.h"
#include "ft_printf.h"

void	ls_print_dirinfo(int is_single, t_flags flags,
							t_file *dir, t_dinfo *dinfo)
{
	if (!is_single)
		ls_print_dir(dir->path ? dir->path : dir->name);
	if (flags.format == LS_FORMAT_LONG)
		ls_print_total(dinfo);
}
