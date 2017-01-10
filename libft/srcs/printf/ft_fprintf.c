/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 15:37:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 15:39:34 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_fprintf(t_stream *stream, const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = ft_vfprintf(stream, format, args);
	va_end(args);
	return (res);
}
