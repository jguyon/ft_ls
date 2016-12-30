/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 23:18:01 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:18:27 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_printf.h"

int		main(void)
{
	tp_test_basics();
	tp_test_ints();
	tp_test_strings();
	tp_test_ptr();
	tp_test_args();
	tp_test_err();
	return (0);
}
