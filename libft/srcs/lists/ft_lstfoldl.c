/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfoldl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 16:51:35 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 02:51:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_lists.h"

void	*ft_lstfoldl(t_list *lst, void *acc, void *(*f)(t_list *el, void *acc))
{
	if (!lst || !(acc = f(lst, acc)))
		return (acc);
	return (ft_lstfoldl(lst->next, acc, f));
}