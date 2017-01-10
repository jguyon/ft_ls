/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_joinr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 10:11:22 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:45:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_joinr(t_dlist *dst, t_dlist *src)
{
	src->head.next->prev = dst->head.prev;
	src->head.prev->next = &(dst->head);
	dst->head.prev->next = src->head.next;
	dst->head.prev = src->head.prev;
}
