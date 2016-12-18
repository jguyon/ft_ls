/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 23:22:17 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:22:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_printf.h"

void	tp_test_ptr(void)
{
	TP_PRINTF_N("hello %n world", int);
	TP_PRINTF_N("hello %ln world", long);
	TP_PRINTF_N("hello %lln world", long long);
	TP_PRINTF_N("hello %hn world", short);
	TP_PRINTF_N("hello %n world", int);
	TP_PRINTF_N("hello %jn world", intmax_t);
	TP_PRINTF_N("hello %zn world", ssize_t);
}
