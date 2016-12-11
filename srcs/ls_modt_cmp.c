/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_modt_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 22:44:04 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/11 23:09:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_modt_cmp(t_list *e1, t_list *e2)
{
	t_ls_file	*f1;
	t_ls_file	*f2;

	f1 = (t_ls_file *)(e1->content);
	f2 = (t_ls_file *)(e2->content);
	if (f1->stat->st_mtime == f2->stat->st_mtime)
		return (ls_lexi_cmp(e1, e2));
	return (f1->stat->st_mtime < f2->stat->st_mtime);
}
