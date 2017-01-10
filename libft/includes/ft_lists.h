/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 02:46:07 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 12:41:26 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LISTS_H
# define FT_LISTS_H

/*
** DEPRECATED - needs rewrite
*/

# include <stddef.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				*ft_lstfoldl(t_list *lst, void *acc,
									void *(*f)(t_list *elem, void *acc));
void				*ft_lstfoldr(t_list *lst, void *acc,
									void *(*f)(t_list *elem, void *acc));
void				ft_lstsort(t_list **lst, int (*f)(t_list *e1, t_list *e2));
void				ft_lstmsort(t_list **lst, int (*f)(t_list *e1, t_list *e2));
void				ft_lstdelcnt(void *content, size_t size);

#endif
