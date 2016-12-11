/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 23:20:28 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:20:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_printf.h"

void	tp_test_err(void)
{
	TP_PRINTF_ERR("%");
	TP_PRINTF_ERR("%0llj", 12);
	TP_PRINTF_ERR("%*1$d", 1, 2);
	TP_PRINTF_ERR("%1$*d", 1, 2);
	TP_PRINTF_ERR("%1$d // %d", 1, 2);
	TP_PRINTF_ERR("%d // %2$d", 1, 2);
}