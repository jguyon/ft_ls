/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 20:31:11 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/25 19:30:54 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

/*
** Main logic of ft_ls
*/

# include "ls_files.h"

/*
** Macros and structure for parsing opts given to the program
*/

# define LS_FLAGS "ARSacdfglmnortux1"

# define LS_FLAG_ALL	'a'
# define LS_FLAG_ALMOST	'A'
# define LS_FLAG_LFMT	'l'
# define LS_FLAG_GRP	'g'
# define LS_FLAG_USR	'o'
# define LS_FLAG_NUM	'n'
# define LS_FLAG_TIME	't'
# define LS_FLAG_SIZE	'S'
# define LS_FLAG_REV	'r'
# define LS_FLAG_REC	'R'
# define LS_FLAG_NODIR	'd'
# define LS_FLAG_LINE	'1'
# define LS_FLAG_STREAM	'm'
# define LS_FLAG_ACROSS 'x'
# define LS_FLAG_ATIM	'u'
# define LS_FLAG_CTIM	'c'
# define LS_FLAG_NOSRT	'f'

# define LS_USAGE_FMT "usage: %s [-%s] [file ...]\n"

typedef enum	e_format {
	LS_FORMAT_LINE = 0,
	LS_FORMAT_LONG = 1,
	LS_FORMAT_STREAM = 2,
	LS_FORMAT_ACROSS = 3,
}				t_format;

typedef enum	e_sorting {
	LS_SORT_LEXI = 0,
	LS_SORT_TIME = 1,
	LS_SORT_SIZE = 2,
	LS_SORT_NONE = 3,
}				t_sorting;

typedef enum	e_time {
	LS_TIME_MODIF = 0,
	LS_TIME_ACCESS = 1,
	LS_TIME_CHANGE = 2,
}				t_time;

typedef enum	e_show {
	LS_SHOW_NOHIDDEN = 0,
	LS_SHOW_ALMOST = 1,
	LS_SHOW_ALL = 2,
}				t_show;

typedef enum	e_bool {
	LS_BOOL_FALSE = 0,
	LS_BOOL_TRUE = 1
}				t_bool;

typedef struct	s_flags {
	t_bool			singlearg : 1;
	t_bool			noowner : 1;
	t_bool			nogroup : 1;
	t_bool			numeric : 1;
	t_bool			reverse : 1;
	t_bool			recur : 1;
	t_bool			nodirs : 1;
	t_show			show : 2;
	t_format		format : 2;
	t_sorting		sorting : 2;
	t_time			time : 2;
}				t_flags;

/*
** Parse command line flags
**
** Returns 0 if successful, -1 if not.
*/
int				ls_parse_flags(int argc, char *const argv[], t_flags *flags);

/*
** Parse files given as arguments
*/
void			ls_parse_files(int argc, char *const argv[],
								t_flags *flags, t_flist *flist);

/*
** Print everything
**
** Returns the appropriate exit status.
*/
int				ls_print_files(t_flags *flags, t_flist *flist);

/*
** Cleanup memory
**
** Should be defined as an atexit callback between
** ls_parse_flags and ls_print_files.
*/
void			ls_cleanup_files(t_flist *flist);

#endif
