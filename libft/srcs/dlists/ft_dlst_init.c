/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 11:01:19 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:44:30 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_init(t_dlist *list, size_t offset)
{
	list->offset = offset;
	list->head.prev = &(list->head);
	list->head.next = &(list->head);
}
