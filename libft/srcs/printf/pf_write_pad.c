/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write_pad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 18:31:07 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 12:52:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_write.h"

size_t	pf_write_pad(t_stream *stream, char c, size_t min_len, size_t real_len)
{
	size_t	count;

	count = real_len;
	while (count < min_len)
	{
		ft_fwrite(&c, 1, stream);
		++count;
	}
	return (count - real_len);
}
