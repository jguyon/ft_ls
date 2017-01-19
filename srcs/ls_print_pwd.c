/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:42:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/19 14:22:16 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"

void	ls_print_pwd(t_finfo *info, size_t uid_width, size_t gid_width)
{
	if (info->owner)
		ft_fprintf(FT_STDOUT, " %*s", -(int)uid_width, info->owner);
	else
		ft_fprintf(FT_STDOUT, " %*u", -(int)uid_width, info->stat->st_uid);
	if (info->group)
		ft_fprintf(FT_STDOUT, "  %*s", -(int)gid_width, info->group);
	else
		ft_fprintf(FT_STDOUT, "  %*u", -(int)gid_width, info->stat->st_gid);
}
