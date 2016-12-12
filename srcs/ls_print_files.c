/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 18:58:01 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 17:06:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file(t_list *el)
{
	t_ls_file	*file;

	file = (t_ls_file *)(el->content);
	ls_printf_out("%s\n", file->name ? file->name : file->path);
}

void		ls_print_files(unsigned int flags, t_list *files)
{
	(void)flags;
	ft_lstiter(files, &print_file);
}
