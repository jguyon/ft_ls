/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:37:41 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 04:08:05 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_convert.h"

int		pf_format_ptr(t_stream *stream, t_pf_info *info, void *arg)
{
	(void)stream;
	if (info->mod == PF_MOD_HH)
		*((signed char *)arg) = (signed char)info->count;
	else if (info->mod == PF_MOD_H)
		*((short *)arg) = (short)info->count;
	else if (info->mod == PF_MOD_L)
		*((long *)arg) = (long)info->count;
	else if (info->mod == PF_MOD_LL)
		*((long long *)arg) = (long long)info->count;
	else if (info->mod == PF_MOD_J)
		*((intmax_t *)arg) = (intmax_t)info->count;
	else if (info->mod == PF_MOD_Z)
		*((ssize_t *)arg) = (ssize_t)info->count;
	else
		*((int *)arg) = (int)info->count;
	return (0);
}
