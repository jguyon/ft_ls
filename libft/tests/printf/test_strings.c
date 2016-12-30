/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 23:22:54 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:23:06 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_printf.h"

void	tp_test_strings(void)
{
	setlocale(LC_ALL, "");

	TP_PRINTF("%s // %s // %ls", "Hello, world!", NULL, NULL);
	TP_PRINTF("%c // %c // %c", 'b', 897, '\0');
	TP_PRINTF("%10s // %010s // %010c // %3s", "hello", "hello", '$', "hello");
	TP_PRINTF("%-10s // %-010s // %-010c // %-3s", "hello", "hello", '$', "hello");
	TP_PRINTF("%10.3s // %10.c // %.10s", "hello", '#', "hello");
	TP_PRINTF("%10s // %.3s", NULL, NULL);

	TP_PRINTF("%ls // %lc // %ls", L"$¢€𐍈", L'𐍈', L"hello");
	TP_PRINTF("%10ls // %10lc // %.5ls", L"$¢€𐍈", L'𐍈', L"$¢€𐍈");
	TP_PRINTF("%ls // %lc // %ls", L"�����", L'�', L"� � � � � � � � � � � � � � � �");
	TP_PRINTF("%lc", L'\0');
	TP_PRINTF("%S // %C", L"$¢€𐍈", L'𐍈');
	TP_PRINTF("%15.5S // %15.2C", L"$¢€𐍈", L'𐍈');

	TP_PRINTF_RES(26, "h.ll. //      h.ll. // h.l", "%r // %10r // %.3r", "h\1ll\2", "h\1ll\2", "h\1ll\2");
}
