/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:34:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/16 12:52:59 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include <time.h>

void	ls_print_time(time_t t)
{
	char	*str;
	time_t	now;

	str = ctime(&t);
	now = time(NULL);
	ft_fprintf(FT_STDOUT, " %.6s %.5s", str + 4,
			   (t + LS_SIX_MONTHS <= now || now + LS_SIX_MONTHS <= t)
			   ? str + 19 : str + 11);
}
