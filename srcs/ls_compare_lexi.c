/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_compare_lexi.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 13:42:14 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 13:43:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_callbacks.h"
#include "ft_strings.h"

int		ls_compare_lexi(t_file *f1, t_file *f2)
{
	return (ft_strcmp(f1->name, f2->name));
}
