/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_singular.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 13:19:25 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:47:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

int		ft_dlst_singular(t_dlist *list)
{
	return (list->head.next != &(list->head)
			&& list->head.next == list->head.prev);
}
