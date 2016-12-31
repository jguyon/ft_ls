/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/31 12:35:19 by jguyon           ###   ########.fr       */
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
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <limits.h>

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
int				g_ls_status;

void			ls_set_progname(char *name);
int				ls_open_streams(void);
int				ls_close_streams(void);
int				ls_printf_out(const char *format, ...);
int				ls_puts_out(const char *s);
int				ls_putc_out(int c);
int				ls_padl_out(const char *s, char padc, size_t len);
int				ls_padr_out(const char *s, char padc, size_t len);
int				ls_printf_err(int errnum, const char *format, ...);

/*
** UTILS
*/

# ifdef __APPLE__
#  define LS_MAJOR(d) (((d) >> (sizeof(dev_t) * 8 - 8)) & 0xff)
#  define LS_MINOR(d) ((d) & 0xff)
# else
#  define LS_MAJOR(d) (((d) >> 8) & 0xff)
#  define LS_MINOR(d) ((d) & 0xff)
# endif

# define LS_OWNER_LEN LOGIN_NAME_MAX
# define LS_GROUP_LEN NSS_BUFLEN_GROUP
# define LS_CACHE_SIZE 317
# define LS_CACHE_EMPTY 0
# define LS_CACHE_VALID 1
# define LS_CACHE_INVALID 2

typedef struct	s_ls_finfo {
	char	*mode;
	char	*links;
	char	*owner;
	char	*group;
	char	*size;
	char	*dmin;
	char	*dmaj;
	char	*time;
	char	*dest;
}				t_ls_finfo;

typedef struct	s_ls_file {
	char			*name;
	char			*path;
	struct stat		*stat;
	t_ls_finfo		*info;
}				t_ls_file;

typedef struct	s_ls_dinfo {
	size_t	total;
	size_t	max_lnk_len;
	size_t	max_usr_len;
	size_t	max_grp_len;
	size_t	max_sze_len;
	size_t	max_maj_len;
	size_t	max_min_len;
}				t_ls_dinfo;

typedef struct	s_ls_fowner {
	int		status;
	char	name[LS_OWNER_LEN];
}				t_ls_fowner;

typedef struct	s_ls_fgroup {
	int		status;
	char	name[LS_GROUP_LEN];
}				t_ls_fgroup;

typedef int		(*t_ls_sort)(t_list *e1, t_list *e2);

char			*ls_join_path(const char *dirname, const char *filename);
int				ls_lexi_cmp(t_list *e1, t_list *e2);
int				ls_modt_cmp(t_list *e1, t_list *e2);
int				ls_lexi_revcmp(t_list *e1, t_list *e2);
int				ls_modt_revcmp(t_list *e1, t_list *e2);
t_ls_sort		ls_sort_fun(unsigned int flags);
char			*ls_file_mode(struct stat *sb);
char			*ls_file_nlinks(struct stat *sb);
char			*ls_file_owner(struct stat *sb);
char			*ls_file_group(struct stat *sb);
char			*ls_file_size(struct stat *sb);
char			*ls_file_time(struct stat *sb);
char			*ls_file_link(const char *path, struct stat *sb);
int				ls_file_devn(struct stat *sb, char **maj, char **min);
t_ls_finfo		*ls_file_info(const char *path, struct stat *sb,
								t_ls_dinfo *dinfo);
void			ls_destroy_finfo(t_ls_finfo **finfo);

/*
** ARG PARSING
*/

# define LS_CHAR_LIN '1'
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
# define LS_HAS_FLAG(flags, f) ((flags & (f)) == (f))

typedef struct	s_ls_args {
	unsigned int	flags : 5;
	size_t			dir_count;
	t_list			*files;
	t_ls_dinfo		*dinfo;
	t_list			*dirs;
}				t_ls_args;

t_ls_args		*ls_parse_args(int ac, char **av);
void			ls_destroy_args(t_ls_args **args);

/*
** FILE LISTING
*/

t_list			*ls_list_files(unsigned int flags, const char *dirname,
								t_ls_dinfo **dinfo);
void			ls_print_files(unsigned int flags, t_list *files,
								t_ls_dinfo *dinfo);
void			ls_destroy_nondirs(unsigned int flags, t_list **files);
void			ls_destroy_files(t_list **files);

#endif
