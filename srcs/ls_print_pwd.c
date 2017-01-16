/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 11:42:49 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 13:14:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"

void	ls_print_pwd(uid_t uid, size_t uid_width, gid_t gid, size_t gid_width)
{
	const char	*owner;
	const char	*group;

	if ((owner = ls_get_owner(uid)))
		ft_fprintf(FT_STDOUT, " %*s", -(int)uid_width, owner);
	else
		ft_fprintf(FT_STDOUT, " %*u", -(int)uid_width, uid);
	if ((group = ls_get_group(gid)))
		ft_fprintf(FT_STDOUT, "  %*s", -(int)gid_width, group);
	else
		ft_fprintf(FT_STDOUT, "  %*u", -(int)gid_width, gid);
}
