/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 23:17:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/26 02:07:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_long_format.h"
#include "ft_memory.h"
#include "ft_chars.h"
#include <time.h>

static time_t	get_time(void)
{
	static time_t	now = (time_t)(-1);

	if (now == (time_t)(-1))
		now = time(NULL);
	return (now);
}

int				ls_format_time(char dst[13], time_t time)
{
	time_t	now;
	char	*str;
	char	*date;
	char	*day_or_year;

	if ((now = get_time()) == (time_t)(-1)
		|| !(str = ctime(&time)))
		return (-1);
	date = str + 4;
	if (time + LS_SIX_MONTHS > now && now + LS_SIX_MONTHS > time)
		day_or_year = str + 11;
	else if (ft_isdigit(str[24]))
	{
		day_or_year = str + 19;
		while (*day_or_year == ' ')
			++day_or_year;
	}
	else
		day_or_year = str + 19;
	ft_memcpy(dst, date, 7);
	ft_memcpy(dst + 7, day_or_year, 5);
	dst[12] = '\0';
	return (0);
}
