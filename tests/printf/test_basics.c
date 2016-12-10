/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 23:19:42 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:19:58 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_printf.h"

void	tp_test_basics(void)
{
	TP_PRINTF("");
	TP_PRINTF("hello");
	TP_PRINTF("I\nhave\tescaped\vchars");
	TP_PRINTF("%% // %% // %%");
}
