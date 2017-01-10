/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cleanup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 12:06:57 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/10 12:14:04 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_program.h"
#include "ft_streams.h"

int		ls_cleanup(int status)
{
	ft_fclose(FT_STDOUT);
	ft_fclose(FT_STDERR);
	return (status);
}
