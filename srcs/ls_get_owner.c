/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_owner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 19:57:43 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/28 18:51:24 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_long_format.h"
#include "ft_memory.h"
#include "ft_strings.h"
#include <stdlib.h>
#include <pwd.h>

static int	is_owner(void *owner, void *uid)
{
	return (((t_owner *)owner)->uid == *((uid_t *)uid));
}

static void	*new_owner(void *uid)
{
	struct passwd	*pw;
	size_t			len;
	t_owner			*owner;

	if (!(pw = getpwuid(*((uid_t *)uid))))
	{
		if (!(owner = (t_owner *)malloc(sizeof(*owner) + 1)))
			return (NULL);
		owner->uid = *((uid_t *)uid);
		owner->name[0] = '\0';
		return (owner);
	}
	len = ft_strlen(pw->pw_name);
	if (!(owner = (t_owner *)malloc(sizeof(*owner) + len + 1)))
		return (NULL);
	owner->uid = *((uid_t *)uid);
	ft_memcpy(owner->name, pw->pw_name, len + 1);
	return (owner);
}

t_cache		g_ls_owners = {
	.is = &is_owner,
	.new = &new_owner,
	.del = &free,
	.list = FT_DLST(g_ls_owners.list, t_owner, node)
};

const char	*ls_get_owner(uid_t uid)
{
	t_owner	*owner;

	if (!(owner = ls_cache_get(&g_ls_owners, &(uid))) || !(owner->name[0]))
		return (NULL);
	return (owner->name);
}
