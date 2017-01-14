/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_owner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 21:35:16 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 00:51:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include <pwd.h>
#include <stdlib.h>

static size_t	put_uid(char *str, uid_t uid, size_t len)
{
	size_t	i;

	i = len;
	str[--i] = '\0';
	str[--i] = uid % 10 + '0';
	while (i && (uid /= 10))
		str[--i] = uid % 10 + '0';
	ft_memmove(str, str + i, len - i);
	return (len - i - 1);
}

static int		is_owner(void *owner, void *uid)
{
	return (((t_owner *)owner)->uid == *((uid_t *)uid));
}

static void		*new_owner(void *uid)
{
	struct passwd	*pw;
	size_t			len;
	t_owner			*owner;

	if ((pw = getpwuid(*((uid_t *)uid))))
	{
		len = ft_strlen(pw->pw_name);
		if (!(owner = (t_owner *)malloc(sizeof(*owner) + len + 1)))
			return (NULL);
		owner->uid = *((uid_t *)uid);
		owner->len = len;
		ft_memcpy(owner->name, pw->pw_name, len + 1);
	}
	else
	{
		len = sizeof(uid_t) * 3;
		if (!(owner = (t_owner *)malloc(sizeof(*owner) + len + 1)))
			return (NULL);
		owner->uid = *((uid_t *)uid);
		owner->len = put_uid(owner->name, *((uid_t *)uid), len + 1);
	}
	return (owner);
}

t_cache			g_ls_owners = {
	.is = &is_owner,
	.new = &new_owner,
	.del = &free,
	.list = LS_DLST(g_ls_owners.list, t_owner, node)
};

size_t			ls_set_owner(t_finfo *info, struct stat *st)
{
	t_owner	*owner;

	if (!(owner = ls_cache_get(&g_ls_owners, &(st->st_uid))))
		return (0);
	info->owner = owner->name;
	return (owner->len);
}
