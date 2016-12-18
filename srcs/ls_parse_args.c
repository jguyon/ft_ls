/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 13:02:29 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/18 18:43:55 by jguyon           ###   ########.fr       */
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
	else if (c != LS_CHAR_LIN)
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
		if (av[i][1] == LS_CHAR_FLAG && av[i][2] == '\0')
		{
			++i;
			break ;
		}
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

static int	parse_one_file(t_ls_args *args, char *name, t_list **el)
{
	t_ls_file	file;
	struct stat	sb;

	*el = NULL;
	ft_bzero(&file, sizeof(file));
	if (!(file.path = ft_strdup(name))
		|| !(file.stat = (struct stat *)ft_memalloc(sizeof(*(file.stat))))
		|| lstat(name, file.stat)
		|| (LS_HAS_FLAG(args->flags, LS_FLAG_LNG)
			&& !(file.info = ls_file_info(file.path, file.stat, args->dinfo)))
		|| !(*el = ft_lstnew(&file, sizeof(file))))
	{
		ls_printf_err(errno, "%s", name);
		ft_memdel((void **)&(file.path));
		ft_memdel((void **)&(file.stat));
		return (1);
	}
	if (S_ISDIR(file.stat->st_mode)
		|| (S_ISLNK(file.stat->st_mode)
			&& !LS_HAS_FLAG(args->flags, LS_FLAG_LNG)
			&& !stat(name, &sb) && S_ISDIR(sb.st_mode)))
		return (1);
	else
		return (0);
}

static void	parse_files(t_ls_args *args, int ac, char **av)
{
	int		i;
	int		res;
	t_list	*el;

	if (ac == 0)
	{
		if ((res = parse_one_file(args, ".", &el)))
			++(args->dir_count);
		if (el)
			ft_lstadd(&(args->dirs), el);
		return ;
	}
	i = 0;
	while (i < ac)
	{
		if ((res = parse_one_file(args, av[i], &el)))
			++(args->dir_count);
		if (res && el)
			ft_lstadd(&(args->dirs), el);
		else if (el)
			ft_lstadd(&(args->files), el);
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
	ft_lstmsort(&(args->files), ls_sort_fun(args->flags));
	ft_lstmsort(&(args->dirs), ls_sort_fun(args->flags));
	return (args);
}
