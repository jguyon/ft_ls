/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 05:41:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 06:08:46 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_printf.h"
#include <locale.h>
#include <limits.h>

TFT_TEST(test_printf_basics)
{
	TP_PRINTF("");
	TP_PRINTF("hello");
	TP_PRINTF("I\nhave\tescaped\vchars");
	TP_PRINTF("%% // %% // %%");
}

TFT_TEST(test_printf_args)
{
	TP_PRINTF("%2$d // %1$d // %1$#x", 42, 21);
	TP_PRINTF("%*u // %.*u", 4, 42, 8, 21);
	TP_PRINTF("%3$*1$.*2$u // %4$*2$.*1$u", 4, 8, 42, 21);
	TP_PRINTF("%2$*1$u // %2$.*1$u", -4, 42);
	TP_PRINTF("%1$d // %% // %1$d", 42);
}

TFT_TEST(test_printf_errs)
{
	TP_PRINTF_ERR("%");
	TP_PRINTF_ERR("%0llj", 12);
	TP_PRINTF_ERR("%*1$d", 1, 2);
	TP_PRINTF_ERR("%1$*d", 1, 2);
	TP_PRINTF_ERR("%1$d // %d", 1, 2);
	TP_PRINTF_ERR("%d // %2$d", 1, 2);
}

TFT_TEST(test_printf_ptrs)
{
	TP_PRINTF_N("hello %n world", int);
	TP_PRINTF_N("hello %ln world", long);
	TP_PRINTF_N("hello %lln world", long long);
	TP_PRINTF_N("hello %hn world", short);
	TP_PRINTF_N("hello %n world", int);
	TP_PRINTF_N("hello %jn world", intmax_t);
	TP_PRINTF_N("hello %zn world", ssize_t);
}

TFT_TEST(test_printf_strings)
{
	setlocale(LC_ALL, "");

	TP_PRINTF("%s // %s // %ls", "Hello, world!", NULL, NULL);
	TP_PRINTF("%c // %c // %c", 'b', 897, '\0');
	TP_PRINTF("%10s // %10c // %3s", "hello", '$', "hello");
	TP_PRINTF("%-10s // %-010s // %-010c // %-3s", "hello", "hello", '$', "hello");
	TP_PRINTF("%10.3s // %10.c // %.10s", "hello", '#', "hello");

	TP_PRINTF("%ls // %lc // %ls", L"$¢€𐍈", L'𐍈', L"hello");
	TP_PRINTF("%10ls // %10lc // %.5ls", L"$¢€𐍈", L'𐍈', L"$¢€𐍈");
	TP_PRINTF("%ls // %lc // %ls", L"�����", L'�', L"� � � � � � � � � � � � � � � �");
	TP_PRINTF("%lc", L'\0');
	TP_PRINTF("%S // %C", L"$¢€𐍈", L'𐍈');
	TP_PRINTF("%15.5S // %15.2C", L"$¢€𐍈", L'𐍈');

	TP_PRINTF_RES(26, "h.ll. //      h.ll. // h.l", "%r // %10r // %.3r", "h\1ll\2", "h\1ll\2", "h\1ll\2");
}

TFT_TEST(test_printf_ints)
{
	TP_PRINTF("%d // %d // %d", 42, -42, 0);
	TP_PRINTF("%d // %d", INT_MAX, INT_MIN);
	TP_PRINTF("%d // %d", LONG_MAX, LONG_MIN);
	TP_PRINTF("%u // %u // %u", 42, 0, UINT_MAX);
	TP_PRINTF("%x // %x // %x", -42, 0, 42);
	TP_PRINTF("%x // %X", UINT_MAX, UINT_MAX);
	TP_PRINTF("%o // %o // %o", -42, 0, 42);
	TP_PRINTF("%i // %i", INT_MAX, INT_MIN);

	TP_PRINTF("%#x // %#X // %#x", 42, 42, 0);
	TP_PRINTF("%#o // %#o", 42, 0);
	TP_PRINTF("% d // % d // % d // % u", 42, -42, 0, 42);
	TP_PRINTF("%+d // %+d // %+d // %+u", 42, -42, 0, 42);
	TP_PRINTF("% +d // % +d // % +d // % +u", 42, -42, 0, 42);

#ifdef __APPLE__
	TP_PRINTF("%D // %D", LONG_MAX, LONG_MIN);
	TP_PRINTF("%U // %u", ULONG_MAX, ULONG_MAX);
	TP_PRINTF("%O // %o", ULONG_MAX, ULONG_MAX);
#endif

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

	TP_PRINTF("%p // %hhp", (void *)"hello", (void *)"hello");
	TP_PRINTF("%040.20p // %020.p", (void *)"hello");

	TP_PRINTF_RES(76, "1001 // 11111111111111111111111111111111 // 11111111111111111111111111111111", "%b // %b // %B", 9, UINT_MAX, ULONG_MAX);
	TP_PRINTF_RES(14, "0b101 // 0B110", "%#b // %#B", 5, 6);
}

void	test_printf(void)
{
	TFT_RUN(test_printf_basics);
	TFT_RUN(test_printf_args);
	TFT_RUN(test_printf_errs);
	TFT_RUN(test_printf_ptrs);
	TFT_RUN(test_printf_strings);
	TFT_RUN(test_printf_ints);
}
