/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_libft.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:33:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 13:33:00 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LIBFT_H
# define TEST_LIBFT_H

# define _GNU_SOURCE
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void	test_dlists(void);
void	test_strings(void);
void	test_streams(void);
void	test_printf(void);

int		g_tft_run;
int		g_tft_fail;

# define TP_NRM "\x1B[0m"
# define TP_RED "\x1B[31m"
# define TP_GRN "\x1B[32m"
# define TP_YLW "\x1B[33m"
# define TP_BLU "\x1B[34m"

# define TFT_RUN(name)														\
	do {																	\
		int	err = 0;														\
		name(&err, #name);													\
		++g_tft_run;														\
		if (err)															\
			++g_tft_fail;													\
	} while (0)

# define TFT_TEST(name)														\
	void	name(int *_err, char *_name)

# define TFT_ASSERT(expr)													\
	do {																	\
		if (!(expr))														\
		{																	\
			printf(TP_YLW "%s" TP_NRM ": " TP_RED "%s" TP_NRM " (%s:%d)\n",	\
					_name, #expr, __FILE__, __LINE__);						\
			*_err = 1;														\
		}																	\
	} while (0)

# define TFT_START															\
	do {																	\
		g_tft_run = 0;														\
		g_tft_fail = 0;														\
	} while (0)

# define TFT_SUMUP															\
	do {																	\
		if (g_tft_fail == 0)												\
			printf(TP_GRN "%1$d / %1$d tests passed\n" TP_NRM, g_tft_run);	\
		else																\
			printf(TP_RED "\n%d / %d tests passed\n" TP_NRM,				\
					g_tft_run - g_tft_fail, g_tft_run);						\
	} while (0)

#endif
