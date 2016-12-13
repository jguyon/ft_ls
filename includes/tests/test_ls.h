/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ls.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 16:36:57 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/13 20:01:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LS_H
# define TEST_LS_H

# include "ft_ls.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <time.h>

void	tls_stmrst(void);
int		tls_outcmp(const char *str);
int		tls_errcmp(const char *str);

void	test_streams(void);
void	test_parse_args(void);
void	test_list_files(void);
void	test_print_files(void);
void	test_destroy_nondirs(void);
void	test_utils(void);

int		g_tls_run;
int		g_tls_fail;

# define TP_NRM "\x1B[0m"
# define TP_RED "\x1B[31m"
# define TP_GRN "\x1B[32m"
# define TP_YLW "\x1B[33m"
# define TP_BLU "\x1B[34m"

# define TLS_RUN(name)														\
	do {																	\
		int	err = 0;														\
		name(&err, #name);													\
		++g_tls_run;														\
		if (err)															\
			++g_tls_fail;													\
	} while (0)

# define TLS_TEST(name)														\
	void	name(int *_err, char *_name)

# define TLS_ASSERT(expr)													\
	do {																	\
		if (!(expr))														\
		{																	\
			printf(TP_YLW "%s" TP_NRM ": " TP_RED "%s" TP_NRM " (%s:%d)\n",	\
					_name, #expr, __FILE__, __LINE__);						\
			*_err = 1;														\
		}																	\
	} while (0)

# define TLS_START															\
	do {																	\
		g_tls_run = 0;														\
		g_tls_fail = 0;														\
	} while (0)

# define TLS_SUMUP															\
	do {																	\
		if (g_tls_fail == 0)												\
			printf(TP_GRN "%1$d / %1$d tests passed\n" TP_NRM, g_tls_run);	\
		else																\
			printf(TP_RED "\n%d / %d tests passed\n" TP_NRM,				\
					g_tls_run - g_tls_fail, g_tls_run);						\
	} while (0)

# define TLS_DIR "/tmp/__test_ls__/"
# define TLS_INIT_FS system("mkdir -p " TLS_DIR " && chmod 777 " TLS_DIR)
# define TLS_STOP_FS system("rm -rf " TLS_DIR)
# define TLS_MKDIR(dir) system("mkdir -p " TLS_DIR dir)
# define TLS_TOUCH(file) system("touch " TLS_DIR file)
# define TLS_TOUCHT(time, file) system("touch -t " time " " TLS_DIR file)
# define TLS_LNS(target, link) system("ln -s " TLS_DIR target " " TLS_DIR link)

#endif
