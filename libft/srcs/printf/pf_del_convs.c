/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_del_convs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:17:52 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 22:18:44 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static void	del_conv(void *content, size_t size)
{
	t_pf_conv	*conv;

	(void)size;
	conv = (t_pf_conv *)content;
	if (conv->format && conv->format->clean_arg)
		conv->format->clean_arg(&(conv->arg));
	ft_memdel((void **)&(conv->info));
	ft_memdel((void *)&conv);
}

void		pf_del_convs(t_list **convs)
{
	ft_lstdel(convs, &del_conv);
}
