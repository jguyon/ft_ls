/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 22:21:42 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 13:58:56 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_strings.h"
#include "ft_simpleio.h"

void	ft_putstr_fd(const char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}
