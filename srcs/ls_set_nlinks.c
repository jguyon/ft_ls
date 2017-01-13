/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_set_nlinks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 18:40:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/13 21:24:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_memory.h"

size_t	ls_set_nlinks(t_finfo *info, struct stat *st)
{
	nlink_t	n;
	size_t	len;

	n = st->st_nlink;
	len = sizeof(info->nlinks);
	info->nlinks[--len] = '\0';
	info->nlinks[--len] = n % 10 + '0';
	while (len && (n /= 10))
		info->nlinks[--len] = n % 10 + '0';
	ft_memmove(info->nlinks, info->nlinks + len, sizeof(info->nlinks) - len);
	return (sizeof(info->nlinks) - len - 1);
}
