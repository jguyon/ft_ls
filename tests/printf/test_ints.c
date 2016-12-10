/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 23:21:14 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:21:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_printf.h"

void	tp_test_ints(void)
{
	TP_PRINTF("%d // %d // %d", 42, -42, 0);
	TP_PRINTF("%d // %d", INT_MAX, INT_MIN);
	TP_PRINTF("%D // %D", LONG_MAX, LONG_MIN);
	TP_PRINTF("%d // %d", LONG_MAX, LONG_MIN);
	TP_PRINTF("%u // %u // %u", 42, 0, UINT_MAX);
	TP_PRINTF("%U // %u", ULONG_MAX, ULONG_MAX);
	TP_PRINTF("%x // %x // %x", -42, 0, 42);
	TP_PRINTF("%x // %X", UINT_MAX, UINT_MAX);
	TP_PRINTF("%o // %o // %o", -42, 0, 42);
	TP_PRINTF("%O // %o", ULONG_MAX, ULONG_MAX);
	TP_PRINTF("%i // %i", INT_MAX, INT_MIN);

	TP_PRINTF("%#x // %#X // %#x", 42, 42, 0);
	TP_PRINTF("%#o // %#O // %#o", 42, 42, 0);
	TP_PRINTF("% d // % d // % d // % u", 42, -42, 0, 42);
	TP_PRINTF("%+d // %+d // %+d // %+u", 42, -42, 0, 42);
	TP_PRINTF("% +d // % +d // % +d // % +u", 42, -42, 0, 42);

	TP_PRINTF("%13d // %+3d", 42, 42);
	TP_PRINTF("%-13d // %+-3d", 42, 42);
	TP_PRINTF("%013d // %0-13d", -42, -42);
	TP_PRINTF("%.13d // %.2d // %.d // %.1d, // %.3d", 42, 42, 0, 42, -42);
	TP_PRINTF("%013.5d // %013.d", 42, 0);
	TP_PRINTF("%#.4o // %#.o // %#13.5o", 42, 0, 42);
	TP_PRINTF("%#13.5x // %#013x", 42, 42);

	TP_PRINTF("%hhd // %hhd // %hhd", SCHAR_MAX, SCHAR_MIN, SHRT_MAX);
	TP_PRINTF("%hd // %hd // %hd", SHRT_MAX, SHRT_MIN, INT_MAX);
	TP_PRINTF("%lld // %lld // %lld", LLONG_MAX, LLONG_MIN, INTMAX_MAX);
	TP_PRINTF("%ld // %ld // %ld", LONG_MAX, LONG_MIN, LLONG_MAX);
	TP_PRINTF("%jd // %jd", INTMAX_MAX, INTMAX_MIN);
	TP_PRINTF("%zd // %zd", SSIZE_MAX, -SSIZE_MAX, INTMAX_MAX);

	TP_PRINTF("%hhu // %hhu", UCHAR_MAX, USHRT_MAX);
	TP_PRINTF("%hu // %hu", USHRT_MAX, UINT_MAX);
	TP_PRINTF("%llu // %llu", ULLONG_MAX, UINTMAX_MAX);
	TP_PRINTF("%lu // %lu", ULONG_MAX, ULONG_MAX);
	TP_PRINTF("%ju // %ju", UINTMAX_MAX);
	TP_PRINTF("%zu // %zu", SIZE_MAX, UINTMAX_MAX);

	TP_PRINTF("%p // %p // %hhp", (void *)"hello", NULL, (void *)"hello");
	TP_PRINTF("%040.20p // %020.p", (void *)"hello", NULL);

	TP_PRINTF_RES(76, "1001 // 11111111111111111111111111111111 // 11111111111111111111111111111111", "%b // %b // %B", 9, UINT_MAX, ULONG_MAX);
	TP_PRINTF_RES(14, "0b101 // 0B110", "%#b // %#B", 5, 6);
}
