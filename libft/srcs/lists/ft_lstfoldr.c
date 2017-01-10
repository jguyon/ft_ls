/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfoldr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:55:46 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:49:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lists.h"

void	*ft_lstfoldr(t_list *lst, void *acc, void *(*f)(t_list *el, void *acc))
{
	if (!lst || !(acc = ft_lstfoldr(lst->next, acc, f)))
		return (acc);
	return (f(lst, acc));
}
