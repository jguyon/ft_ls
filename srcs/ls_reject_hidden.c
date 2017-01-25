/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_reject_hidden.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:38:15 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 20:57:09 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"

int		ls_reject_hidden(t_file *file)
{
	return (file->name[0] == '.');
}

int		ls_reject_implied(t_file *file)
{
	return (file->name[0] == '.'
			&& (file->name[1] == '\0'
				|| (file->name[1] == '.'
					&& file->name[2] == '\0')));
}
