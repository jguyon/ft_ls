/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 23:49:24 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 23:57:10 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_sort	ls_sort_fun(unsigned int flags)
{
	if (LS_HAS_FLAG(flags, LS_FLAG_TME | LS_FLAG_REV))
		return (&ls_modt_revcmp);
	else if (LS_HAS_FLAG(flags, LS_FLAG_TME))
		return (&ls_modt_cmp);
	else if (LS_HAS_FLAG(flags, LS_FLAG_REV))
		return (&ls_lexi_revcmp);
	else
		return (&ls_lexi_cmp);
}
