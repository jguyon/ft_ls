/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 05:41:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 16:41:07 by jguyon           ###   ########.fr       */
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
	TP_PRINTF("%*s // %*s", 10, "hello", -10, "hello");
	TP_PRINTF("%.*s // %.*s", 3, "hello", -3, "hello");
	TP_PRINTF("%*.*s // %*.*s", 10, 3, "hello", -10, 3, "hello");
}

TFT_TEST(test_printf_errs)
{
	TP_PRINTF_ERR("%");
	TP_PRINTF_ERR("%a", 12);
	TP_PRINTF_ERR("%0llj", 12);
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

	TP_PRINTF("%s // %s", "Hello, world!", NULL);
	TP_PRINTF("%10s // %10s // %10s", "hello", "hellohello", "hellohellohello");
	TP_PRINTF("%.s // %.10s // %.10s // %.10s", "hello", "hello", "hellohello", "hellohellohello");
	TP_PRINTF("%10.5s // %10.5s", "hello", "hellohello");
	TP_PRINTF("%-s // %-10s", "hello", "hello");
	TP_PRINTF("%ls // %10ls // %.5ls", L"$¢€", L"$¢€", L"$¢€");
	TP_PRINTF("%c // %c", 'h', '\0');
	TP_PRINTF("%10c // %1c", 'h', 'a');
	TP_PRINTF("%10lc // %10lc", L'€', L'h');
}

TFT_TEST(test_printf_ints)
{
	TP_PRINTF("%d // %d // %d", 42, -42, 0);
	TP_PRINTF("%d // %d // %d // %d", INT_MAX, INT_MIN, LONG_MAX, LONG_MIN);
	TP_PRINTF("%hhd // %hhd // %hhd // %hhd", SCHAR_MAX, SCHAR_MIN, SHRT_MAX, SHRT_MIN);
	TP_PRINTF("%hd // %hd // %hd // %hd", SHRT_MAX, SHRT_MIN, INT_MAX, INT_MIN);
	TP_PRINTF("%ld // %ld // %ld // %ld", LONG_MAX, LONG_MIN, LLONG_MAX, LLONG_MIN);
	TP_PRINTF("%lld // %lld // %lld // %lld", LLONG_MAX, LLONG_MIN, INTMAX_MAX, INTMAX_MIN);
	TP_PRINTF("%jd // %jd", INTMAX_MAX, INTMAX_MIN);
	TP_PRINTF("%zd // %zd", SSIZE_MAX, INTMAX_MIN);
	TP_PRINTF("%5d // %5d // %5d", 42, -42, INT_MAX);
	TP_PRINTF("%.5d // %.5d // %.5d", 42, -42, INT_MAX);
	TP_PRINTF(".d // .d", 42, 0);
	TP_PRINTF("%5.5d // %5.5d // %5.5d", 42, -42, INT_MAX);
	TP_PRINTF("%-5d // %-5d // %-5d", 42, -42, INT_MAX);
	TP_PRINTF("%05d // %05d // %05d", 42, -42, INT_MAX);
	TP_PRINTF("%0-5d // %0-5d // %0-5d", 42, -42, INT_MAX);
	TP_PRINTF("%+d // %+d", 42, -42);
	TP_PRINTF("% d // % d", 42, -42);
	TP_PRINTF("%+ d // %+ d", 42, -42);
	TP_PRINTF("%0+22.12hhi", 42);
	TP_PRINTF("%u // %u // %u", 42, -42, 0);
	TP_PRINTF("%u // %u", UINT_MAX, ULONG_MAX);
	TP_PRINTF("%hhu // %hhu", UCHAR_MAX, USHRT_MAX);
	TP_PRINTF("%hu // %hu", USHRT_MAX, UINT_MAX);
	TP_PRINTF("%lu // %lu", ULONG_MAX, ULLONG_MAX);
	TP_PRINTF("%llu // %llu", ULLONG_MAX, UINTMAX_MAX);
	TP_PRINTF("%ju", UINTMAX_MAX);
	TP_PRINTF("%zu // %zu", SIZE_MAX, INT_MIN);
	TP_PRINTF("%0 22.12hhu", 42);
	TP_PRINTF("%+o // %#o // %.5o // %#.5o", 42, 42, 42, 42);
	TP_PRINTF("%+x // %#X // %.5X // %#.5X", 42, 42, 42, 42);
	TP_PRINTF("%p // %10.5p", "hello", "hello");
	TP_PRINTF_RES(3, "0x0", "%p", NULL);
}

TFT_TEST(test_printf_sprintf)
{
	char	str[256];

	TFT_ASSERT(ft_sprintf(str, "%s", "hello") == 5);
	TFT_ASSERT(strcmp(str, "hello") == 0);
	TFT_ASSERT(ft_snprintf(str, 3, "%s", "hello") == 5);
	TFT_ASSERT(strcmp(str, "hel") == 0);
	TFT_ASSERT(ft_snprintf(NULL, 0, "%s", "hello") == 5);
}

void	test_printf(void)
{
	TFT_RUN(test_printf_basics);
	TFT_RUN(test_printf_errs);
	TFT_RUN(test_printf_strings);
	TFT_RUN(test_printf_args);
	TFT_RUN(test_printf_ints);
	TFT_RUN(test_printf_ptrs);
	TFT_RUN(test_printf_sprintf);
}
