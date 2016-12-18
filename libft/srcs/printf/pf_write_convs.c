/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_write_convs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:46:42 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 22:50:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static void	*write_conv(t_list *el, void *acc)
{
	t_pf_conv		*conv;
	t_pf_conv_acc	*conv_acc;
	int				res;

	conv = (t_pf_conv *)(el->content);
	conv_acc = (t_pf_conv_acc *)acc;
	ft_fwrite(conv->prev, conv->len, conv_acc->stream);
	conv_acc->count += conv->len;
	res = 0;
	if (conv->format)
	{
		conv->info->count = conv_acc->count;
		if (conv->info->width_arg >= 0 && conv->info->width < 0)
		{
			conv->info->width = -(conv->info->width);
			conv->info->flags |= PF_FLAG_NEG;
		}
		res = conv->format->format(conv_acc->stream, conv->info, conv->arg);
		conv_acc->count += res;
	}
	if (res < 0 || ft_ferror(conv_acc->stream))
		return (NULL);
	return (acc);
}

int			pf_write_convs(t_stream *stream, t_list *convs)
{
	t_pf_conv_acc	acc;

	acc.count = 0;
	acc.stream = stream;
	if (!(ft_lstfoldl(convs, &acc, &write_conv)))
		acc.count = -1;
	return (acc.count);
}
