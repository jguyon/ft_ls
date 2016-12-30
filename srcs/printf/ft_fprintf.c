/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:59:28 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:02:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

int		ft_fprintf(t_stream *stream, const char *format, ...)
{
	va_list	ap;
	int		res;

	va_start(ap, format);
	res = ft_vfprintf(stream, format, ap);
	va_end(ap);
	return (res);
}
