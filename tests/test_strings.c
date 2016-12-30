/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:59:10 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/30 21:52:19 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_libft.h"

TFT_TEST(test_memset)
{
	char	mem_ft[200] = {0};
	char	mem_lc[200] = {0};

	TFT_ASSERT(memcmp(ft_memset(mem_ft, 1, 200), memset(mem_lc, 1, 200), 200) == 0);
	TFT_ASSERT(memcmp(ft_memset(mem_ft + 3, 2, 197), memset(mem_lc + 3, 2, 197), 197) == 0);
}

TFT_TEST(test_memcpy)
{
	char	mem_ft[200] = {0};
	char	mem_lc[200] = {0};
	char	src[200] = {0};

	memset(src, 1, 100);
	memset(src + 100, 2, 100);
	TFT_ASSERT(memcmp(ft_memcpy(mem_ft, src, 200), memcpy(mem_lc, src, 200), 200) == 0);
	TFT_ASSERT(memcmp(ft_memcpy(mem_ft + 3, src, 197), memcpy(mem_lc + 3, src, 197), 197) == 0);
}

TFT_TEST(test_strlen)
{
	char	str[256] = {0};

	strcpy(str, "hello");
	TFT_ASSERT(ft_strlen(str) == strlen(str));
	strcpy(str, "hello world hello world hello world hello world");
	TFT_ASSERT(ft_strlen(str) == strlen(str));
	strcpy(str, "");
	TFT_ASSERT(ft_strlen(str) == strlen(str));
	strcpy(str, "hello world");
	TFT_ASSERT(ft_strlen(str) == strlen(str));
}

TFT_TEST(test_strnlen)
{
	char	str[256] = {0};

	strcpy(str, "hello world hello world hello world hello world hello world");
	TFT_ASSERT(ft_strnlen(str, 256) == strnlen(str, 256));
	TFT_ASSERT(ft_strnlen(str + 1, 17) == strnlen(str + 1, 17));
}

TFT_TEST(test_memccpy)
{
	char	mem_ft[256] = {0};
	char	mem_lc[256] = {0};
	char	src[256] = {0};

	TFT_ASSERT(strcmp(ft_memccpy(mem_ft, "hello world", 'o', 12),
					  memccpy(mem_lc, "hello world", 'o', 12)) == 0);
	TFT_ASSERT(strcmp(mem_ft, mem_lc) == 0);
	bzero(mem_ft, 256);
	bzero(mem_lc, 256);
	TFT_ASSERT(ft_memccpy(mem_ft, "hello world", 'o', 3)
			   == memccpy(mem_lc, "hello world", 'o', 3));
	TFT_ASSERT(strcmp(mem_ft, mem_lc) == 0);
	bzero(mem_ft, 256);
	bzero(mem_lc, 256);
	memset(src, 'a', 256);
	src[197] = 'b';
	TFT_ASSERT(strcmp(ft_memccpy(mem_ft, src, 'b', 243),
					  memccpy(mem_lc, src, 'b', 243)) == 0);
	TFT_ASSERT(strcmp(mem_ft, mem_lc) == 0);
}

TFT_TEST(test_memmove)
{
	char	mem_ft[256] = {0};
	char	mem_lc[256] = {0};

	strcpy(mem_ft, "hello world hello world hello world");
	strcpy(mem_lc, "hello world hello world hello world");
	TFT_ASSERT(strcmp(ft_memmove(mem_ft, mem_ft + 3, 200),
					  memmove(mem_lc, mem_lc + 3, 200)) == 0);
	TFT_ASSERT(strcmp(ft_memmove(mem_ft + 3, mem_ft, 200),
					  memmove(mem_lc + 3, mem_lc, 200)) == 0);
}

TFT_TEST(test_memchr)
{
	char	*mem = "abcdef\0ghijklmnopqrstuvwxyz0123456789";

	TFT_ASSERT(ft_memchr(mem, '0', 37) == memchr(mem, '0', 37));
	TFT_ASSERT(ft_memchr(mem, '\0', 37) == memchr(mem, '\0', 37));
	TFT_ASSERT(ft_memchr(mem, '@', 37) == memchr(mem, '@', 37));
}

TFT_TEST(test_memcmp)
{
	char	*mem = "abcdef\0ghijklmnopqrstuvwxyz0123456789";
	char	cmp[37];

	memcpy(cmp, mem, 37);
	TFT_ASSERT(ft_memcmp(mem, cmp, 37) == memcmp(mem, cmp, 37));
	--cmp[20];
	TFT_ASSERT(ft_memcmp(mem, cmp, 37) == memcmp(mem, cmp, 37));
	++cmp[6];
	TFT_ASSERT(ft_memcmp(mem, cmp, 37) == memcmp(mem, cmp, 37));
}

TFT_TEST(test_strdup)
{
	char	*str_ft;
	char	*str_lc;

	str_ft = ft_strdup("qwertyuiopasdfghjklzxcvbnm0123456789");
	str_lc = strdup("qwertyuiopasdfghjklzxcvbnm0123456789");
	TFT_ASSERT(strcmp(str_ft, str_lc) == 0);
	free(str_ft);
	free(str_lc);
	str_ft = ft_strdup("hello");
	str_lc = strdup("hello");
	TFT_ASSERT(strcmp(str_ft, str_lc) == 0);
	free(str_ft);
	free(str_lc);
	str_ft = ft_strdup("");
	str_lc = strdup("");
	TFT_ASSERT(strcmp(str_ft, str_lc) == 0);
	free(str_ft);
	free(str_lc);
}

TFT_TEST(test_strcpy)
{
	char	str_ft[256];
	char	str_lc[256];
	char	*src = "qwertyuiopasdfghjklzxcvbnm0123456789";

	TFT_ASSERT(strcmp(ft_strcpy(str_ft, src), strcpy(str_lc, src)) == 0);
	TFT_ASSERT(strcmp(ft_strcpy(str_ft, src + 30), strcpy(str_lc, src + 30)) == 0);
	TFT_ASSERT(strcmp(ft_strcpy(str_ft, src + 36), strcpy(str_lc, src + 36)) == 0);
}

TFT_TEST(test_strncpy)
{
	char	str_ft[256];
	char	str_lc[256];
	char	*src = "qwertyuiopasdfghjklzxcvbnm0123456789";

	memset(str_ft, 'a', 256);
	memset(str_lc, 'a', 256);
	TFT_ASSERT(memcmp(ft_strncpy(str_ft, src, 30), strncpy(str_lc, src, 30), 256) == 0);
	memset(str_ft, 'a', 256);
	memset(str_lc, 'a', 256);
	TFT_ASSERT(memcmp(ft_strncpy(str_ft, src + 30, 6), strncpy(str_lc, src + 30, 6), 256) == 0);
	memset(str_ft, 'a', 256);
	memset(str_lc, 'a', 256);
	TFT_ASSERT(memcmp(ft_strncpy(str_ft, src + 36, 3), strncpy(str_lc, src + 36, 3), 256) == 0);
}

TFT_TEST(test_strcat)
{
	char	str_ft[256] = {0};
	char	str_lc[256] = {0};
	char	*src = "qwertyuiopasdfghjklzxcvbnm0123456789";

	TFT_ASSERT(strcmp(ft_strcat(str_ft, src), strcat(str_lc, src)) == 0);
	TFT_ASSERT(strcmp(ft_strcat(str_ft, src), strcat(str_lc, src)) == 0);
	TFT_ASSERT(strcmp(ft_strcat(str_ft, ""), strcat(str_lc, "")) == 0);
}

TFT_TEST(test_strncat)
{
	char	str_ft[256] = {0};
	char	str_lc[256] = {0};
	char	*src = "qwertyuiopasdfghjklzxcvbnm0123456789";

	TFT_ASSERT(strcmp(ft_strncat(str_ft, src, 40), strncat(str_lc, src, 40)) == 0);
	TFT_ASSERT(strcmp(ft_strncat(str_ft, src, 30), strncat(str_lc, src, 30)) == 0);
}

TFT_TEST(test_strlcat)
{
	char	str_ft[256] = {0};
	char	str_lc[256] = {0};
	char	*src = "qwertyuiopasdfghjklzxcvbnm0123456789";

	TFT_ASSERT(ft_strlcat(str_ft, src, 37) == strlcat(str_lc, src, 37));
	TFT_ASSERT(strcmp(str_ft, str_lc) == 0);
	TFT_ASSERT(ft_strlcat(str_ft, src, 47) == strlcat(str_lc, src, 47));
	TFT_ASSERT(strcmp(str_ft, str_lc) == 0);
	TFT_ASSERT(ft_strlcat(str_ft, src, 256) == strlcat(str_lc, src, 256));
	TFT_ASSERT(strcmp(str_ft, str_lc) == 0);
}

TFT_TEST(test_strchrnul)
{
	char	*str = "qwertyuiopasdfghjklzxcvbnm0123456789";

	TFT_ASSERT(ft_strchrnul(str, 't') == strchrnul(str, 't'));
	TFT_ASSERT(ft_strchrnul(str, '7') == strchrnul(str, '7'));
	TFT_ASSERT(ft_strchrnul(str, '\0') == strchrnul(str, '\0'));
	TFT_ASSERT(ft_strchrnul(str, '$') == strchrnul(str, '$'));
}

TFT_TEST(test_strchr)
{
	char	*str = "qwertyuiopasdfghjklzxcvbnm0123456789";

	TFT_ASSERT(ft_strchr(str, 't') == strchr(str, 't'));
	TFT_ASSERT(ft_strchr(str, '7') == strchr(str, '7'));
	TFT_ASSERT(ft_strchr(str, '\0') == strchr(str, '\0'));
	TFT_ASSERT(ft_strchr(str, '$') == strchr(str, '$'));
}

TFT_TEST(test_strrchr)
{
	char	*str = "qwertyuiopasdfghjklzxcvbnm0123456789q";

	TFT_ASSERT(ft_strrchr(str, 't') == strrchr(str, 't'));
	TFT_ASSERT(ft_strrchr(str, '7') == strrchr(str, '7'));
	TFT_ASSERT(ft_strrchr(str, '\0') == strrchr(str, '\0'));
	TFT_ASSERT(ft_strrchr(str, '$') == strrchr(str, '$'));
	TFT_ASSERT(ft_strrchr(str, 'q') == strrchr(str, 'q'));
}

TFT_TEST(test_strcmp)
{
	char	*str = "qwertyuiopasdfghjklzxcvbnm0123456789q";
	char	cpy[256];

	strcpy(cpy, str);
	TFT_ASSERT(ft_strcmp(str, cpy) == strcmp(str, cpy));
	cpy[28] = '$';
	TFT_ASSERT(ft_strcmp(str, cpy) == strcmp(str, cpy));
	cpy[4] = '\0';
	TFT_ASSERT(ft_strcmp(str, cpy) == strcmp(str, cpy));
}

TFT_TEST(test_strncmp)
{
	char	str[256] = "qwertyuiopasdfghjklzxcvbnm0123456789q";
	char	cpy[256];

	strcpy(cpy, str);
	TFT_ASSERT(ft_strncmp(str, cpy, 256) == strncmp(str, cpy, 256));
	TFT_ASSERT(ft_strncmp(str, cpy, 5) == strncmp(str, cpy, 5));
	cpy[28] = '$';
	TFT_ASSERT(ft_strncmp(str, cpy, 28) == strncmp(str, cpy, 28));
	TFT_ASSERT(ft_strncmp(str, cpy, 29) == strncmp(str, cpy, 29));
	cpy[4] = '\0';
	TFT_ASSERT(ft_strncmp(str, cpy, 4) == strncmp(str, cpy, 4));
	TFT_ASSERT(ft_strncmp(str, cpy, 5) == strncmp(str, cpy, 5));
}

TFT_TEST(test_strstr)
{
	char	str[256] = "qwertyuiopasdfghjklzxcvbnm0123456789q";

	TFT_ASSERT(ft_strstr(str, "012") == strstr(str, "012"));
	TFT_ASSERT(ft_strstr(str, "0124") == strstr(str, "0124"));
	TFT_ASSERT(ft_strstr(str, "qz") == strstr(str, "qz"));
	TFT_ASSERT(ft_strstr(str, "") == strstr(str, ""));
	TFT_ASSERT(ft_strstr(str, "qw") == strstr(str, "qw"));
}

TFT_TEST(test_strnstr)
{
	char	str[256] = "qwertyuiopasdfghjklzxcvbnm0123456789";

	TFT_ASSERT(ft_strnstr(str, "0123456789", 36) == strnstr(str, "0123456789", 36));
	TFT_ASSERT(ft_strnstr(str, "0123456789", 35) == strnstr(str, "0123456789", 35));
	TFT_ASSERT(ft_strnstr(str, "0123456789", 25) == strnstr(str, "0123456789", 25));
}

TFT_TEST(test_strclr)
{
	char	str[] = "qwertyuiopasdfghjklzxcvbnm0123456789";
	char	zro[256] = {0};

	ft_strclr(str);
	TFT_ASSERT(memcmp(str, zro, 36) == 0);
}

TFT_TEST(test_strjoin)
{
	char	s1[] = "qwertyuiopasdfghjklzxcvbnm";
	char	s2[] = "0123456789";
	char	*join = NULL;

	join = ft_strjoin(s1, s2);
	TFT_ASSERT(memcmp(s1, join, 26) == 0);
	TFT_ASSERT(memcmp(s2, join + 26, 11) == 0);
	free(join);
}

TFT_TEST(test_strsub)
{
	char	str[] = "qwertyuiopasdfghjklzxcvbnm0123456789";
	char	*sub = NULL;

	sub = ft_strsub(str, 3, 31);
	TFT_ASSERT(ft_memcmp(sub, str + 3, 31) == 0);
	free(sub);
}

void	test_strings(void)
{
	TFT_RUN(test_memset);
	TFT_RUN(test_memcpy);
	TFT_RUN(test_memccpy);
	TFT_RUN(test_memmove);
	TFT_RUN(test_memchr);
	TFT_RUN(test_memcmp);
	TFT_RUN(test_strlen);
	TFT_RUN(test_strnlen);
	TFT_RUN(test_strdup);
	TFT_RUN(test_strcpy);
	TFT_RUN(test_strncpy);
	TFT_RUN(test_strcat);
	TFT_RUN(test_strncat);
	TFT_RUN(test_strlcat);
	TFT_RUN(test_strchrnul);
	TFT_RUN(test_strchr);
	TFT_RUN(test_strrchr);
	TFT_RUN(test_strcmp);
	TFT_RUN(test_strncmp);
	TFT_RUN(test_strstr);
	TFT_RUN(test_strnstr);
	TFT_RUN(test_strclr);
	TFT_RUN(test_strjoin);
	TFT_RUN(test_strsub);
}
