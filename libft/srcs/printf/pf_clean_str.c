/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_clean_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:16:34 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 04:07:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "priv/pf_convert.h"

void	pf_clean_str(void **arg)
{
	t_pf_str	*str_arg;

	if (*arg)
	{
		str_arg = *((t_pf_str **)arg);
		ft_memdel((void **)&(str_arg->str));
		ft_memdel((void **)&(str_arg->wstr));
		ft_memdel((void **)arg);
	}
}
