/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_dirinfo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 13:40:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/11 13:43:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_printf.h"

void	ls_print_dirinfo(t_flags flags, t_file *dir)
{
	(void)flags;
	ft_fprintf(FT_STDOUT, "%s:\n", dir->path ? dir->path : dir->name);
}
