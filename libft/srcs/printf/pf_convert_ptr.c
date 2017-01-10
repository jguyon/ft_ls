/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_convert_ptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 15:33:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 15:39:02 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include <unistd.h>
#include "priv/pf_convert.h"

int		pf_convert_ptr(t_stream *stream, t_pf_info *info, va_list args)
{
	void	*n;

	(void)stream;
	n = va_arg(args, void *);
	if (info->mod == HH)
		*((signed char *)n) = (signed char)(info->count);
	else if (info->mod == H)
		*((short *)n) = (short)(info->count);
	else if (info->mod == L)
		*((long *)n) = (long)(info->count);
	else if (info->mod == LL)
		*((long long *)n) = (long long)(info->count);
	else if (info->mod == J)
		*((intmax_t *)n) = (intmax_t)(info->count);
	else if (info->mod == Z)
		*((ssize_t *)n) = (ssize_t)(info->count);
	else
		*((int *)n) = (int)(info->count);
	return (0);
}
