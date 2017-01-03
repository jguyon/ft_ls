/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 23:59:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 02:50:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/ft_lists.h"

static void	lstdel(t_list *list, void (*del)(void *, size_t))
{
	t_list	*next;

	if (!list)
		return ;
	next = list->next;
	if (del)
		del(list->content, list->content_size);
	free(list);
	return (lstdel(next, del));
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	lstdel(*alst, del);
	*alst = NULL;
}
