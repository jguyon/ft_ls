/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_prepare_cols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 14:22:21 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 18:16:29 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ls_tty.h"

static t_dlist_node	*first_node(t_dlist *list, int rev)
{
	return (rev ? ft_dlst_last(list) : ft_dlst_first(list));
}

static t_dlist_node	*next_col(t_dlist *list, t_dlist_node *node,
								size_t rows, int rev)
{
	if (rev)
	{
		while (rows && (node = ft_dlst_prev(list, node)))
			--rows;
	}
	else
	{
		while (rows && (node = ft_dlst_next(list, node)))
			--rows;
	}
	return (node);
}

static void			move_node(t_dlist *dst, t_dlist_node *node, int rev)
{
	ft_dlst_remove(node);
	if (rev)
		ft_dlst_pushl(dst, node);
	else
		ft_dlst_pushr(dst, node);
}

static void			order_cols(t_dlist *list, size_t rows, int rev)
{
	t_dlist			new;
	t_dlist_node	*curr;
	t_dlist_node	*next;

	ft_dlst_init(&new, list->offset);
	while (rows)
	{
		curr = first_node(list, rev);
		while (curr)
		{
			next = next_col(list, curr, rows, rev);
			move_node(&new, curr, rev);
			curr = next;
		}
		--rows;
	}
	ft_dlst_joinl(list, &new);
}

void				ls_prepare_cols(t_cols_dinfo *dinfo, t_dlist *files,
									int rev)
{
	if (dinfo->count > 0)
	{
		if (dinfo->colwidth > 0 && ls_tty_width() > dinfo->colwidth)
			dinfo->cols = ls_tty_width() / dinfo->colwidth;
		else
			dinfo->cols = 1;
		dinfo->rows = dinfo->count / dinfo->cols
						+ !!(dinfo->count % dinfo->cols);
		while (dinfo->count / dinfo->rows
				+ !!(dinfo->count % dinfo->rows)
				< dinfo->cols)
		{
			--(dinfo->cols);
			dinfo->rows = dinfo->count / dinfo->cols
							+ !!(dinfo->count % dinfo->cols);
		}
		if (dinfo->rows > 1)
			order_cols(files, dinfo->rows, rev);
	}
}
