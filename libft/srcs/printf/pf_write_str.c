/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/08 20:22:05 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 20:23:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_write.h"

size_t	pf_write_str(t_stream *stream, const char *str, size_t len)
{
	ft_fwrite(str, len, stream);
	return (len);
}
