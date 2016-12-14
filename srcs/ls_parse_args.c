/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:02:29 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/14 20:38:06 by jguyon           ###   ########.fr       */
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
	{
		ls_printf_err(0, "%s%c\n%s", LS_ERR_ILLEGAL, c, LS_ERR_USAGE);
		return (0);
	}
	return (1);
}

static int	parse_flags(t_ls_args *args, int ac, char **av)
{
	int		i;
	char	*str;

	i = 0;
	while (i < ac && av[i][0] && av[i][1] && av[i][0] == LS_CHAR_FLAG)
	{
		str = av[i] + 1;
		while (*str)
		{
			if (!(parse_one_flag(args, *str)))
				return (-1);
			++str;
		}
		++i;
	}
	return (i);
}

static void	parse_one_file(t_ls_args *args, char *name)
{
	t_ls_file	file;
	t_list		*el;

	file.name = NULL;
	file.stat = NULL;
	file.path = NULL;
	file.info = NULL;
	if (!(file.path = ft_strdup(name))
		|| !(file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat))))
		|| (!LS_HAS_FLAG(args->flags, LS_FLAG_LNG) && stat(name, file.stat))
		|| (LS_HAS_FLAG(args->flags, LS_FLAG_LNG)
			&& (lstat(name, file.stat)
			|| !(file.info = ls_file_info(file.path, file.stat, args->dinfo))))
		|| !(el = ft_lstnew(&file, sizeof(file))))
	{
		ls_printf_err(errno, "%s", name);
		ft_memdel((void **)&(file.path));
		ft_memdel((void **)&(file.stat));
		return ;
	}
	if (S_ISDIR(file.stat->st_mode))
		ft_lstadd(&(args->dirs), el);
	else
		ft_lstadd(&(args->files), el);
}

static void	parse_files(t_ls_args *args, int ac, char **av)
{
	int		i;

	if (ac == 0)
	{
		parse_one_file(args, ".");
		return ;
	}
	i = 0;
	while (i < ac)
	{
		parse_one_file(args, av[i]);
		++i;
	}
}

t_ls_args	*ls_parse_args(int ac, char **av)
{
	t_ls_args	*args;
	int			i;

	if (ac < 0 || !(args = ft_memalloc(sizeof(*args))))
		return (NULL);
	if ((i = parse_flags(args, ac, av)) < 0
		|| (LS_HAS_FLAG(args->flags, LS_FLAG_LNG)
		&& !(args->dinfo = (t_ls_dinfo *)ft_memalloc(sizeof(*(args->dinfo))))))
	{
		ls_destroy_args(&args);
		return (NULL);
	}
	parse_files(args, ac - i, av + i);
	ft_lstsort(&(args->files), ls_sort_fun(args->flags));
	ft_lstsort(&(args->dirs), ls_sort_fun(args->flags));
	return (args);
}
