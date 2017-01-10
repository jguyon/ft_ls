/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_joinl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 09:56:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:45:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlists.h"

void	ft_dlst_joinl(t_dlist *dst, t_dlist *src)
{
	src->head.next->prev = &(dst->head);
	src->head.prev->next = dst->head.next;
	dst->head.next->prev = src->head.prev;
	dst->head.next = src->head.next;
}
