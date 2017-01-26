/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cleanup_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 16:16:27 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 02:09:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ls_long_format.h"

void	ls_cleanup_files(t_flist *flist)
{
	ls_cache_clear(&g_ls_owners);
	ls_cache_clear(&g_ls_groups);
	ls_flist_clear(flist);
}
