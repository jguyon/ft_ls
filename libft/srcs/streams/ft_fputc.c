/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 20:03:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:59:39 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_streams.h"

int		ft_fputc(int c, t_stream *stream)
{
	char	uc;

	uc = (unsigned char)c;
	if (ft_fwrite(&uc, 1, stream) != 1)
		return (-1);
	return (uc);
}
