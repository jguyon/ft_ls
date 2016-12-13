/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_destroy_nondirs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 01:27:40 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 02:43:53 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	destroy_nondirs(t_list **files)
{
	t_ls_file	*file;
	t_list		*el;

	if (*files)
	{
		el = *files;
		file = (t_ls_file *)(el->content);
		if (!S_ISDIR(file->stat->st_mode)
			|| ft_strcmp(file->name, ".") == 0
			|| ft_strcmp(file->name, "..") == 0)
		{
			*files = el->next;
			el->next = NULL;
			ls_destroy_files(&el);
			return (destroy_nondirs(files));
		}
		return (destroy_nondirs(&((*files)->next)));
	}
}

void		ls_destroy_nondirs(unsigned int flags, t_list **files)
{
	if (LS_HAS_FLAG(flags, LS_FLAG_REC))
		destroy_nondirs(files);
	else
		ls_destroy_files(files);
}
