/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 23:17:08 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 23:17:37 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_PRINTF_H
# define TEST_PRINTF_H

# include "libftprintf.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <string.h>
# include <inttypes.h>
# include <limits.h>
# include <locale.h>

void		tp_test_basics(void);
void		tp_test_ints(void);
void		tp_test_strings(void);
void		tp_test_ptr(void);
void		tp_test_args(void);
void		tp_test_err(void);

# define TP_TEST_FILE "/tmp/test_ft_printf"

# define TP_READ_PRINTF(res, dst, pf, format, ...)							\
	do {																	\
		int		fd;															\
		int		i;															\
																			\
		res = -2;															\
		dst = NULL;															\
		if ((fd = open(TP_TEST_FILE, O_CREAT | O_TRUNC | O_RDWR)) < 0)		\
			break ;															\
		fchmod(fd, S_IRUSR | S_IWUSR);										\
		res = pf(fd, format, ##__VA_ARGS__);								\
		if (res >= 0)														\
		{																	\
			lseek(fd, 0, SEEK_SET);											\
			if (!(dst = (char *)malloc(sizeof(*dst) * (res + 2))))			\
			{																\
				res = -2;													\
				close(fd);													\
				break ;														\
			}																\
			i = 0;															\
			while (i <= res && (read(fd, dst + i, 1)) == 1)					\
				++i;														\
			dst[i] = '\0';													\
		}																	\
		close(fd);															\
	} while (0)

# define TP_NRM "\x1B[0m"
# define TP_RED "\x1B[31m"
# define TP_GRN "\x1B[32m"
# define TP_YLW "\x1B[33m"
# define TP_BLU "\x1B[34m"

# define TP_PRINTF(format, ...)												\
	do {																	\
		int		res_ft;														\
		int		res_pf;														\
		char	*str_ft;													\
		char	*str_pf;													\
																			\
		puts(TP_BLU "printf(" #format ", " #__VA_ARGS__")" TP_NRM);			\
		TP_READ_PRINTF(res_pf, str_pf, dprintf, format, ##__VA_ARGS__);		\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf, format, ##__VA_ARGS__);	\
		if (res_ft == -2 || res_pf == -2)									\
		{																	\
			puts(TP_RED "Error while testing" TP_NRM);						\
			free(str_ft);													\
			free(str_pf);													\
			break ;															\
		}																	\
		printf(TP_YLW "%d" TP_NRM " == " TP_YLW "%d" TP_NRM " ?\n",			\
				res_ft, res_pf);											\
		printf(TP_YLW "\"%s\"" TP_NRM " == " TP_YLW "\"%s\"" TP_NRM " ?\n",	\
				str_ft, str_pf);											\
		if (res_ft == res_pf && strcmp(str_ft, str_pf) == 0)				\
			puts(TP_GRN "SUCCESS\n" TP_NRM);								\
		else																\
			puts(TP_RED "FAILURE\n" TP_NRM);								\
		free(str_ft);														\
		free(str_pf);														\
	} while (0)

# define TP_PRINTF_N(format, type, ...)										\
	do {																	\
		int		res_ft;														\
		int		res_pf;														\
		char	*str_ft;													\
		char	*str_pf;													\
		void	*n_ft;														\
		void	*n_pf;														\
																			\
		n_ft = malloc(sizeof(type));										\
		n_pf = malloc(sizeof(type));										\
		puts(TP_BLU "printf(" #format ", " #__VA_ARGS__ ", &n)" TP_NRM);	\
		TP_READ_PRINTF(res_pf, str_pf, dprintf,								\
				format, ##__VA_ARGS__, n_pf);								\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf,							\
				format, ##__VA_ARGS__, n_ft);								\
		if (res_ft == -2 || res_pf == -2)									\
		{																	\
			puts(TP_RED "Error while testing" TP_NRM);						\
			free(str_ft);													\
			free(str_pf);													\
			free(n_ft);														\
			free(n_pf);														\
			break ;															\
		}																	\
		printf(TP_YLW "%d" TP_NRM " == " TP_YLW "%d" TP_NRM " ?\n",			\
				res_ft, res_pf);											\
		printf(TP_YLW "\"%s\"" TP_NRM " == " TP_YLW "\"%s\"" TP_NRM " ?\n",	\
				str_ft, str_pf);											\
		printf(TP_YLW "%jd" TP_NRM " == " TP_YLW "%jd" TP_NRM " ?\n",		\
				(intmax_t)(*((type *)n_ft)), (intmax_t)(*((type *)n_pf)));	\
		if (res_ft == res_pf && strcmp(str_ft, str_pf) == 0					\
				&& *((type *)n_ft) == *((type *)n_pf))						\
			puts(TP_GRN "SUCCESS\n" TP_NRM);								\
		else																\
			puts(TP_RED "FAILURE\n" TP_NRM);								\
		free(str_ft);														\
		free(str_pf);														\
		free(n_ft);															\
		free(n_pf);															\
	} while (0)

# define TP_PRINTF_RES(res, str, format, ...)								\
	do {																	\
		int		res_ft;														\
		char	*str_ft;													\
																			\
		puts(TP_BLU "printf(" #format ", " #__VA_ARGS__ ")" TP_NRM);		\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf, format, ##__VA_ARGS__);	\
		if (res_ft == -2)													\
		{																	\
			puts(TP_RED "Error while testing" TP_NRM);						\
			free(str_ft);													\
			break ;															\
		}																	\
		printf(TP_YLW "%d" TP_NRM " == " TP_YLW "%d" TP_NRM " ?\n",			\
				res_ft, res);												\
		printf(TP_YLW "\"%s\"" TP_NRM " == " TP_YLW "\"%s\"" TP_NRM " ?\n",	\
				str_ft, str);												\
		if (res_ft == res && strcmp(str_ft, str) == 0)						\
			puts(TP_GRN "SUCCESS\n" TP_NRM);								\
		else																\
			puts(TP_RED "FAILURE\n" TP_NRM);								\
		free(str_ft);														\
	} while (0)

# define TP_PRINTF_ERR(format, ...)											\
	do {																	\
		int		res_ft;														\
		char	*str_ft;													\
																			\
		puts(TP_BLU "printf(" #format ", " #__VA_ARGS__ ")" TP_NRM);		\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf, format, ##__VA_ARGS__);	\
		if (res_ft == -2)													\
		{																	\
			puts(TP_RED "Error while testing" TP_NRM);						\
			free(str_ft);													\
			break ;															\
		}																	\
		printf(TP_YLW "%d" TP_NRM " == " TP_YLW "%d" TP_NRM " ?\n",			\
				res_ft, -1);												\
		printf(TP_YLW "%p" TP_NRM " == " TP_YLW "%p" TP_NRM " ?\n",			\
				str_ft, NULL);												\
		if (res_ft == -1 && str_ft == NULL)									\
			puts(TP_GRN "SUCCESS\n" TP_NRM);								\
		else																\
			puts(TP_RED "FAILURE\n" TP_NRM);								\
		free(str_ft);														\
} while (0)

#endif
