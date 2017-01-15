/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_group.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 01:00:09 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 01:10:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include <grp.h>
#include <stdlib.h>

static size_t	put_gid(char *str, gid_t gid, size_t len)
{
	size_t	i;

	i = len;
	str[--i] = '\0';
	str[--i] = gid % 10 + '0';
	while (i && (gid /= 10))
		str[--i] = gid % 10 + '0';
	ft_memmove(str, str + i, len - i);
	return (len - i - 1);
}

static int		is_group(void *group, void *gid)
{
	return (((t_group *)group)->gid == *((gid_t *)gid));
}

static void		*new_group(void *gid)
{
	struct group	*gr;
	size_t			len;
	t_group			*group;

	if ((gr = getgrgid(*((gid_t *)gid))))
	{
		len = ft_strlen(gr->gr_name);
		if (!(group = (t_group *)malloc(sizeof(*group) + len + 1)))
			return (NULL);
		group->gid = *((gid_t *)gid);
		group->len = len;
		ft_memcpy(group->name, gr->gr_name, len + 1);
	}
	else {
		len = sizeof(gid_t) * 3;
		if (!(group = (t_group *)malloc(sizeof(*group) + len + 1)))
			return (NULL);
		group->gid = *((gid_t *)gid);
		group->len = put_gid(group->name, *((gid_t *)gid), len + 1);
	}
	return (group);
}

t_cache			g_ls_groups = {
	.is = &is_group,
	.new = &new_group,
	.del = &free,
	.list = LS_DLST(g_ls_groups.list, t_group, node)
};

size_t			ls_set_group(t_finfo *info, struct stat *st)
{
	t_group	*group;

	if (!(group = ls_cache_get(&g_ls_groups, &(st->st_gid))))
		return (0);
	info->group = group->name;
	return (group->len);
}
