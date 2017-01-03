/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_fmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:06:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 04:05:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_memory.h"
#include "priv/pf_convert.h"

void	*pf_arg_fmt(t_pf_info *info, va_list ap)
{
	t_pf_str	*arg;

	(void)ap;
	(void)info;
	if (!(arg = (t_pf_str *)ft_memalloc(sizeof(*arg))))
		return (NULL);
	if ((arg->str = (char *)ft_memalloc(sizeof(*(arg->str)))))
	{
		arg->str[0] = '%';
		arg->len = 1;
	}
	else
		ft_memdel((void **)&arg);
	return (arg);
}
