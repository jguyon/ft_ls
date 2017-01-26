/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_compare_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:55:59 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 11:34:47 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"

int		ls_compare_time(t_file *f1, t_file *f2)
{
	struct timespec	*t1;
	struct timespec	*t2;

	t1 = g_get_time(f1->lstat);
	t2 = g_get_time(f2->lstat);
	if (t1->tv_sec > t2->tv_sec)
		return (-1);
	if (t1->tv_sec < t2->tv_sec)
		return (1);
	if (t1->tv_nsec > t2->tv_nsec)
		return (-1);
	if (t1->tv_nsec < t2->tv_nsec)
		return (1);
	return (ls_compare_lexi(f1, f2));
}
