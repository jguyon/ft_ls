/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:02:29 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 21:17:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	parse_one_flag(t_ls_args *args, char c)
{
	if (c == LS_CHAR_LNG)
		LS_ADD_FLAG(args->flags, LS_FLAG_LNG);
	else if (c == LS_CHAR_REC)
		LS_ADD_FLAG(args->flags, LS_FLAG_REC);
	else if (c == LS_CHAR_ALL)
		LS_ADD_FLAG(args->flags, LS_FLAG_ALL);
	else if (c == LS_CHAR_REV)
		LS_ADD_FLAG(args->flags, LS_FLAG_REV);
	else if (c == LS_CHAR_TME)
		LS_ADD_FLAG(args->flags, LS_FLAG_TME);
	else
		return (0);
	return (1);
}

static int	parse_flags(t_ls_args *args, int ac, char **av)
{
	int		i;
	char	*str;

	i = 1;
	while (i < ac && av[i][0] && av[i][1] && av[i][0] == LS_CHAR_FLAG)
	{
		str = av[i] + 1;
		while (*str)
		{
			if (!(parse_one_flag(args, *str)))
				return (0);
			++str;
		}
		++i;
	}
	return (i);
}

t_ls_args	*ls_parse_args(int ac, char **av)
{
	t_ls_args	*args;
	int			i;
	t_list		*el;

	if (ac < 1 || !(args = ft_memalloc(sizeof(*args))))
		return (NULL);
	if (!(args->cmd = ft_strdup(av[0]))
		|| !(i = parse_flags(args, ac, av)))
	{
		ls_destroy_args(&args);
		return (NULL);
	}
	while (i < ac)
	{
		if (!(el = ft_lstnew(av[i], sizeof(av[i]))))
		{
			ls_destroy_args(&args);
			return (NULL);
		}
		ft_lstadd(&(args->files), el);
		++i;
	}
	return (args);
}
