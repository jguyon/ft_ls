/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 18:58:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 15:04:45 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file(t_list *el)
{
	t_ls_file	*file;

	file = (t_ls_file *)(el->content);
	ls_puts_out(file->name ? file->name : file->path);
	ls_putc_out('\n');
}

static void	print_file_size(t_ls_file *file, t_ls_dinfo *dinfo)
{
	if (file->info->dmaj && file->info->dmin)
	{
		ls_padl_out(file->info->dmaj, ' ', dinfo->max_maj_len + 2);
		ls_putc_out(',');
		ls_padl_out(file->info->dmin, ' ', dinfo->max_min_len + 1);
	}
	else
		ls_padl_out(file->info->size, ' ', dinfo->max_sze_len + 2);
}

static void	print_file_name(t_ls_file *file)
{
	ls_puts_out(file->name ? file->name : file->path);
	if (file->info->dest)
	{
		ls_puts_out(" -> ");
		ls_puts_out(file->info->dest);
	}
}

static void	*print_long_file(t_list *el, void *acc)
{
	t_ls_file	*file;
	t_ls_dinfo	*dinfo;

	file = (t_ls_file *)(el->content);
	dinfo = (t_ls_dinfo *)acc;
	ls_puts_out(file->info->mode);
	ls_padl_out(file->info->links, ' ', dinfo->max_lnk_len + 2);
	ls_putc_out(' ');
	ls_padr_out(file->info->owner, ' ', dinfo->max_usr_len + 2);
	ls_padr_out(file->info->group, ' ', dinfo->max_grp_len);
	print_file_size(file, dinfo);
	ls_putc_out(' ');
	ls_puts_out(file->info->time);
	ls_putc_out(' ');
	print_file_name(file);
	ls_putc_out('\n');
	return (acc);
}

void		ls_print_files(unsigned int flags, t_list *files, t_ls_dinfo *dinfo)
{
	if (LS_HAS_FLAG(flags, LS_FLAG_LNG) && dinfo)
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
