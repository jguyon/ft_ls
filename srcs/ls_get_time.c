/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_get_time.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:15:13 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 11:37:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"

#ifdef __APPLE__
# define MTIMESPEC(stat) (stat->st_mtimespec)
# define CTIMESPEC(stat) (stat->st_ctimespec)
# define ATIMESPEC(stat) (stat->st_atimespec)
#elif linux
# define MTIMESPEC(stat) (stat->st_mtim)
# define CTIMESPEC(stat) (stat->st_ctim)
# define ATIMESPEC(stat) (stat->st_atim)
#endif

struct timespec	*(*g_get_time)(struct stat *st) = &ls_get_mtime;

struct timespec	*ls_get_mtime(struct stat *st)
{
	return (&MTIMESPEC(st));
}

struct timespec	*ls_get_ctime(struct stat *st)
{
	return (&CTIMESPEC(st));
}

struct timespec	*ls_get_atime(struct stat *st)
{
	return (&ATIMESPEC(st));
}
