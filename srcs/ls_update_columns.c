/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_update_columns.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 18:44:03 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 19:09:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_strings.h"

void	ls_update_columns(t_dinfo *info, const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len + 1 > info->colwidth)
		info->colwidth = len + 1;
}
