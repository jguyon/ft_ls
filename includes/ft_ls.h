/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/12 16:18:08 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libftstream.h"
# include "libftprintf.h"

# include <unistd.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>

/*
** ERROR MESSAGES
*/

# define LS_ERR_USAGE	"usage: ft_ls [-lRart] [file ...]"
# define LS_ERR_ILLEGAL "illegal option -- "

/*
** STD OUTPUT
*/

# define LS_DEFAULT_PROGNAME	"ft_ls"
# define LS_DEFAULT_STDOUT		1
# define LS_DEFAULT_STDERR		2

int				g_ls_stdout_fd;
int				g_ls_stderr_fd;
t_stream		*g_ls_stdout;
t_stream		*g_ls_stderr;
char			*g_ls_progname;

void			ls_set_progname(char *name);
int				ls_open_streams(void);
int				ls_close_streams(void);
int				ls_printf_out(const char *format, ...);
int				ls_printf_err(int errnum, const char *format, ...);

/*
** ARG PARSING
*/

# define LS_CHAR_LNG 'l'
# define LS_CHAR_REC 'R'
# define LS_CHAR_ALL 'a'
# define LS_CHAR_REV 'r'
# define LS_CHAR_TME 't'
# define LS_CHAR_FLAG '-'

# define LS_FLAG_LNG 1
# define LS_FLAG_REC 2
# define LS_FLAG_ALL 4
# define LS_FLAG_REV 8
# define LS_FLAG_TME 16

# define LS_ADD_FLAG(flags, f) (flags |= f)
# define LS_HAS_FLAG(flags, f) (flags & f)

typedef struct	s_ls_args {
	unsigned int	flags : 5;
	t_list			*files;
	t_list			*dirs;
}				t_ls_args;

t_ls_args		*ls_parse_args(int ac, char **av);
void			ls_destroy_args(t_ls_args **args);

/*
** FILE LISTING
*/

typedef struct	s_ls_file {
	char			*name;
	char			*path;
	struct stat		*stat;
}				t_ls_file;

t_list			*ls_map_args(unsigned int flags, t_list *files);
t_list			*ls_list_files(unsigned int flags, const char *dirname);
void			ls_print_files(unsigned int flags, t_list *files);
void			ls_destroy_files(t_list **files);

/*
** UTILS
*/

char			*ls_join_path(const char *dirname, const char *filename);
int				ls_lexi_cmp(t_list *e1, t_list *e2);
int				ls_modt_cmp(t_list *e1, t_list *e2);
int				ls_lexi_revcmp(t_list *e1, t_list *e2);
int				ls_modt_revcmp(t_list *e1, t_list *e2);

#endif
