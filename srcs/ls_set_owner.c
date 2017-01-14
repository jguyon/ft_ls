/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_owner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 21:35:16 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/14 21:23:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_strings.h"
#include "ft_memory.h"
#include <pwd.h>

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

size_t			ls_set_owner(t_finfo *info, struct stat *st)
{
	static t_owner	cache[LS_CACHE_SIZE];
	size_t			i;
	struct passwd	*pw;

	i = st->st_uid % LS_CACHE_SIZE;
	if (!(cache[i].cached) || cache[i].uid != st->st_uid)
	{
		cache[i].uid = st->st_uid;
		cache[i].cached = 1;
		if ((pw = getpwuid(st->st_uid)))
		{
			cache[i].len = ft_strlen(pw->pw_name);
			ft_memcpy(cache[i].owner, pw->pw_name, cache[i].len + 1);
		}
		else
			cache[i].len = put_uid(cache[i].owner, cache[i].uid,
									sizeof(cache[i].owner));
	}
	ft_memcpy(info->owner, cache[i].owner, cache[i].len + 1);
	return (cache[i].len);
}
