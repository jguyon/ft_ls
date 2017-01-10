/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 22:23:10 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:57:48 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_simpleio.h"

void	ft_putendl_fd(char const *str, int fd)
{
	if (str)
	{
		ft_putstr_fd(str, fd);
		ft_putchar_fd('\n', fd);
	}
}
