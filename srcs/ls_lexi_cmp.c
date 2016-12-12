/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_lexi_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 22:29:32 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 17:47:12 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_lexi_cmp(t_list *e1, t_list *e2)
{
	t_ls_file	*f1;
	t_ls_file	*f2;

	f1 = (t_ls_file *)(e1->content);
	f2 = (t_ls_file *)(e2->content);
	if (f1->name && f2->name)
		return (ft_strcmp(f1->name, f2->name) > 0);
	else if (f1->path && f2->path)
		return (ft_strcmp(f1->path, f2->path) > 0);
	else
		return (0);
}
