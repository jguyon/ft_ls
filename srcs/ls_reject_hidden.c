/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_reject_hidden.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:38:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/27 13:07:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"

int		ls_reject_hidden(const char *name)
{
	return (name[0] == '.');
}

int		ls_reject_implied(const char *name)
{
	return (name[0] == '.'
			&& (name[1] == '\0'
				|| (name[1] == '.'
					&& name[2] == '\0')));
}
