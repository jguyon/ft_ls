/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 12:44:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/24 18:23:52 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_FILES_H
# define LS_FILES_H

# include "ft_dlists.h"
# include <sys/stat.h>
# include <dirent.h>

typedef int		t_ftype;

# define LS_FTYP_UNKNOWN	0
# define LS_FTYP_FIFO		DT_FIFO
# define LS_FTYP_CHR		DT_CHR
# define LS_FTYP_DIR		DT_DIR
# define LS_FTYP_BLK		DT_BLK
# define LS_FTYP_REG		DT_REG
# define LS_FTYP_LNK		DT_LNK
# define LS_FTYP_SOCK		DT_SOCK
# define LS_FTYP_WHT		DT_WHT

typedef void	t_file_del(void *info);

typedef struct	s_file {
	t_ftype			ltype;
	t_ftype			type;
	const char		*name;
	char			*path;
	struct stat		*stat;
	struct stat		*lstat;
	void			*info;
	t_file_del		*del;
	t_dlist_node	node;
}				t_file;

int				ls_file_lstat(t_file *file);
int				ls_file_stat(t_file *file);
int				ls_file_ltype(t_file *file);
int				ls_file_type(t_file *file);
void			ls_file_del(t_file **file);

typedef void	t_flist_init(void *dirinfo);
typedef int		t_flist_insert(void *dirinfo, t_file *file);
typedef void	t_flist_print(void *dirinfo, t_file *file);
typedef int		t_flist_compare(t_file *f1, t_file *f2);
typedef int		t_flist_reject(t_file *file);

typedef struct	s_flist {
	int				reverse;
	int				recur;
	void			*dirinfo;
	t_flist_init	*init;
	t_flist_insert	*insert;
	t_flist_print	*print;
	t_flist_compare	*compare;
	t_flist_reject	*reject;
	t_dlist			files;
	t_dlist			dirs;
}				t_flist;

int				ls_flist_init(t_flist *flist);
void			ls_flist_add(t_flist *flist, const char *path, int nofollow);
void			ls_flist_start(t_flist *flist);
t_file			*ls_flist_next(t_flist *flist);
void			ls_flist_print(t_flist *flist);

#endif
