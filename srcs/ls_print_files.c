/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 18:58:01 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 22:10:21 by jguyon           ###   ########.fr       */
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
	ls_printf_out("%s  %*s %-*s  %-*s", file->info->mode,
			dinfo->max_lnk_len, file->info->links,
			dinfo->max_usr_len, file->info->owner,
			dinfo->max_grp_len, file->info->group);
	if (file->info->dmaj && file->info->dmin)
		ls_printf_out("  %*s, %*s", dinfo->max_maj_len, file->info->dmaj,
									dinfo->max_min_len, file->info->dmin);
	else
		ls_printf_out("  %*s", dinfo->max_sze_len, file->info->size);
	ls_printf_out(" %s", file->info->time);
	if (file->info->dest)
		ls_printf_out(" %s -> %s\n", file->name ? file->name : file->path,
				file->info->dest);
	else
		ls_printf_out(" %s\n", file->name ? file->name : file->path);
	return (acc);
}

void		ls_print_files(unsigned int flags, t_list *files, t_ls_dinfo *dinfo)
{
	(void)flags;
	if (dinfo)
	{
		if (dinfo->max_maj_len > 0 && dinfo->max_maj_len < 3)
			dinfo->max_maj_len = 3;
		if (dinfo->max_min_len > 0 && dinfo->max_min_len < 3)
			dinfo->max_min_len = 3;
		if (dinfo->max_min_len && dinfo->max_maj_len
			&& dinfo->max_sze_len < dinfo->max_maj_len + dinfo->max_min_len + 2)
			dinfo->max_sze_len = dinfo->max_maj_len + dinfo->max_min_len + 2;
		ft_lstfoldl(files, dinfo, &print_long_file);
	}
	else
		ft_lstiter(files, &print_file);
}
