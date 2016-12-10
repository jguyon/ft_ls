/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:02:29 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 17:52:18 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_args	*ls_parse_args(int ac, char **av)
{
	t_ls_args	*args;
	int			i;
	t_list		*el;

	if (ac < 1 || !(args = ft_memalloc(sizeof(*args))))
		return (NULL);
	if (!(args->cmd = ft_strdup(av[0])))
		return (NULL);
	args->files = NULL;
	i = 1;
	while (i < ac)
	{
		if (!(el = ft_lstnew(av[i], sizeof(av[i]))))
		{
			ft_lstdel(&(args->files), &ft_lstdelcnt);
			return (NULL);
		}
		ft_lstadd(&(args->files), el);
		++i;
	}
	return (args);
}
