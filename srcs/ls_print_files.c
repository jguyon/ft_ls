/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 18:58:01 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 22:18:35 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file(t_list *el)
{
	t_ls_file	*file;

	file = (t_ls_file *)(el->content);
	ls_printf_out("%s\n", file->name ? file->name : file->path);
}

static void	*print_long_file(t_list *el, void *acc)
{
	t_ls_file	*file;
	t_ls_dinfo	*dinfo;

	file = (t_ls_file *)(el->content);
	dinfo = (t_ls_dinfo *)acc;
	ls_printf_out("%s %*s %*s %*s %*s %s %s", file->info->mode,
			dinfo->max_lnk_len, file->info->links,
			dinfo->max_usr_len, file->info->owner,
			dinfo->max_grp_len, file->info->group,
			dinfo->max_sze_len, file->info->size,
			file->info->time, file->name ? file->name : file->path);
	if (file->info->dest)
		ls_printf_out(" -> %s\n", file->info->dest);
	else
		ls_printf_out("\n");
	return (acc);
}

void		ls_print_files(unsigned int flags, t_list *files, t_ls_dinfo *dinfo)
{
	(void)flags;
	if (dinfo)
		ft_lstfoldl(files, dinfo, &print_long_file);
	else
		ft_lstiter(files, &print_file);
}
