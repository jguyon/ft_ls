/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 05:30:39 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 15:12:25 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_PRINTF_H
# define TEST_PRINTF_H

# include "libft.h"
# include "test_libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <string.h>

# define TP_TEST_FILE "/tmp/test_ft_printf"

# define TP_READ_PRINTF(res, dst, pf, format, ...)						\
	do {																\
		int		fd;														\
		int		i;														\
																		\
		res = -2;														\
		dst = NULL;														\
		if ((fd = open(TP_TEST_FILE, O_CREAT | O_TRUNC | O_RDWR)) < 0)	\
			break ;														\
		fchmod(fd, S_IRUSR | S_IWUSR);									\
		res = pf(fd, format, ##__VA_ARGS__);							\
		if (res >= 0)													\
		{																\
			lseek(fd, 0, SEEK_SET);										\
			if (!(dst = (char *)malloc(sizeof(*dst) * (res + 2))))		\
			{															\
				res = -2;												\
				close(fd);												\
				break ;													\
			}															\
			i = 0;														\
			while (i <= res && (read(fd, dst + i, 1)) == 1)				\
				++i;													\
			dst[i] = '\0';												\
		}																\
		close(fd);														\
	} while (0)

# define TP_PRINTF(format, ...)												\
	do {																	\
		int		res_ft;														\
		int		res_pf;														\
		char	*str_ft;													\
		char	*str_pf;													\
																			\
		TP_READ_PRINTF(res_pf, str_pf, dprintf, format, ##__VA_ARGS__);		\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf, format, ##__VA_ARGS__);	\
		TFT_ASSERT(res_ft != -2 && res_pf != -2);							\
		if (res_ft == -2 || res_pf == -2)									\
		{																	\
			free(str_ft);													\
			free(str_pf);													\
			break ;															\
		}																	\
		TFT_ASSERT(res_ft == res_pf);										\
		if (str_ft && str_pf)												\
			TFT_ASSERT(strcmp(str_ft, str_pf) == 0);						\
		else																\
			TFT_ASSERT(str_ft == str_pf);									\
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
		TP_READ_PRINTF(res_pf, str_pf, dprintf,								\
					   format, ##__VA_ARGS__, (type *)n_pf);				\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf,							\
					   format, ##__VA_ARGS__, (type *)n_ft);				\
		TFT_ASSERT(res_ft != -2 && res_pf != -2);							\
		if (res_ft == -2 || res_pf == -2)									\
		{																	\
			free(str_ft);													\
			free(str_pf);													\
			free(n_ft);														\
			free(n_pf);														\
			break ;															\
		}																	\
		TFT_ASSERT(res_ft == res_pf);										\
		if (!str_ft || !str_pf)												\
			TFT_ASSERT(str_ft == str_pf);									\
		else																\
			TFT_ASSERT(strcmp(str_ft, str_pf) == 0);						\
		TFT_ASSERT(*((type *)n_ft) == *((type *)n_pf));						\
		free(str_ft);														\
		free(str_pf);														\
		free(n_ft);															\
		free(n_pf);															\
	} while (0)

# define TP_PRINTF_RES(res, str, format, ...)							\
	do {																\
		int		res_ft;													\
		char	*str_ft;												\
																		\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf, format,				\
			##__VA_ARGS__);												\
		TFT_ASSERT(res_ft != -2);										\
		if (res_ft == -2)												\
		{																\
			free(str_ft);												\
			break ;														\
		}																\
		TFT_ASSERT(res_ft == res);										\
		TFT_ASSERT(strcmp(str_ft, str) == 0);							\
		free(str_ft);													\
	} while (0)

# define TP_PRINTF_ERR(format, ...)										\
	do {																\
		int		res_ft;													\
		char	*str_ft;												\
																		\
		TP_READ_PRINTF(res_ft, str_ft, ft_dprintf, format,				\
			##__VA_ARGS__);												\
		TFT_ASSERT(res_ft != -2);										\
		if (res_ft == -2)												\
		{																\
			free(str_ft);												\
			break ;														\
		}																\
		TFT_ASSERT(res_ft == -1);										\
		TFT_ASSERT(str_ft == NULL);										\
		free(str_ft);													\
	} while (0)

#endif
