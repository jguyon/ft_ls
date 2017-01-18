/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_print_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:34:55 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/18 15:46:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_format.h"
#include "ft_printf.h"
#include "ft_chars.h"
#include <time.h>

void	ls_print_time(time_t t)
{
	char	*str;
	time_t	now;
	char	*date;
	char	*day_or_year;

	str = ctime(&t);
	now = time(NULL);
	date = str + 4;
	if (t + LS_SIX_MONTHS > now && now + LS_SIX_MONTHS > t)
		day_or_year = str + 11;
	else if (ft_isdigit(str[24]))
	{
		day_or_year = str + 19;
		while (*day_or_year == ' ')
			++day_or_year;
	}
	else
		day_or_year = str + 19;
	ft_fprintf(FT_STDOUT, " %.6s %.5s", date, day_or_year);
}
