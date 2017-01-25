/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_compare_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:05:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 14:07:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"

int		ls_compare_size(t_file *f1, t_file *f2)
{
	if (f1->lstat->st_size > f2->lstat->st_size)
		return (-1);
	if (f1->lstat->st_size < f2->lstat->st_size)
		return (1);
	return (ls_compare_lexi(f1, f2));
}
