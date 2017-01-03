/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_arg_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:12:33 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 04:07:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_convert.h"

void	*pf_arg_ptr(t_pf_info *info, va_list ap)
{
	void	*n;

	(void)info;
	n = va_arg(ap, void *);
	return (n);
}
