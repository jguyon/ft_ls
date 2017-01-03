/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:04:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 03:23:38 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_strings.h"
#include "libft/ft_streams.h"

int		ft_fputs(const char *s, t_stream *stream)
{
	size_t	len;

	len = ft_strlen(s);
	if (ft_fwrite(s, len, stream) != len)
		return (-1);
	return (len);
}
