/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_foreachr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 11:57:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:44:03 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_foreachr(t_dlist *list, void *acc, t_dlist_iterator itr)
{
	ft_dlst_foreachr_from(list, list->head.prev, acc, itr);
}
