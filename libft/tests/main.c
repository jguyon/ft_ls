/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 18:15:02 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/09 20:52:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_libft.h"

int		main(void)
{
	TFT_START;
	test_strings();
	test_lists();
	test_dlists();
	test_streams();
	test_printf();
	TFT_SUMUP;
}
