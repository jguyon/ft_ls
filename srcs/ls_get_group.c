/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_group.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 20:16:18 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 02:06:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_long_format.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <stdlib.h>
#include <grp.h>

static int	is_group(void *group, void *gid)
{
	return (((t_group *)group)->gid == *((gid_t *)gid));
}

static void	*new_group(void *gid)
{
	struct group	*gr;
	size_t			len;
	t_group			*group;

	if (!(gr = getgrgid(*((gid_t *)gid))))
	{
		if (!(group = (t_group *)malloc(sizeof(*group) + 1)))
			return (NULL);
		group->gid = *((gid_t *)gid);
		group->name[0] = '\0';
		return (group);
	}
	len = ft_strlen(gr->gr_name);
	if (!(group = (t_group *)malloc(sizeof(*group) + len + 1)))
		return (NULL);
	group->gid = *((gid_t *)gid);
	ft_memcpy(group->name, gr->gr_name, len + 1);
	return (group);
}

t_cache		g_ls_groups = {
	.is = &is_group,
	.new = &new_group,
	.del = &free,
	.list = LS_DLST(g_ls_groups.list, t_group, node)
};

const char	*ls_get_group(gid_t gid)
{
	t_group	*group;

	if (!(group = ls_cache_get(&g_ls_groups, &gid)) || !(group->name[0]))
		return (NULL);
	return (group->name);
}
