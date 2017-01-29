/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_files.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/24 12:44:47 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/29 12:56:49 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_FILES_H
# define LS_FILES_H

/*
** Abstraction for traversing directories
*/

# include "ft_dlists.h"
# include <sys/stat.h>
# include <dirent.h>

/*
** Type holding the type of a file
*/
typedef int		t_ftype;

/*
** Constants reprensenting types of files
*/
# define LS_FTYP_UNKNOWN	0
# define LS_FTYP_FIFO		DT_FIFO
# define LS_FTYP_CHR		DT_CHR
# define LS_FTYP_DIR		DT_DIR
# define LS_FTYP_BLK		DT_BLK
# define LS_FTYP_REG		DT_REG
# define LS_FTYP_LNK		DT_LNK
# define LS_FTYP_SOCK		DT_SOCK
# ifdef __APPLE__
#  define LS_FTYP_WHT		DT_WHT
# else
#  define LS_FTYP_WHT		(-1)
# endif

/*
** Test the type of a file using its mode
*/
# define LS_ISFIFO(m)		S_ISFIFO(m)
# define LS_ISCHR(m)		S_ISCHR(m)
# define LS_ISDIR(m)		S_ISDIR(m)
# define LS_ISBLK(m)		S_ISBLK(m)
# define LS_ISREG(m)		S_ISREG(m)
# define LS_ISLNK(m)		S_ISLNK(m)
# define LS_ISSOCK(m)		S_ISSOCK(m)
# ifdef __APPLE__
#  define LS_ISWHT(m)		S_ISWHT(m)
# else
#  define LS_ISWHT(m)		0
# endif

/*
** Function type for deleting info associated to a file
*/
typedef void	t_file_del(void *info);

/*
** Struct holding information about the file
**
** @ltype: type of the file
** @type: type of the file or its target if it is a link
** @name: name of the file
** @path: full path of the file relative to the current directory
** @lstat: stat of the file
** @stat: stat of the file or its target if it is a link
** @info: additional info
** @del: function used to free @info if necessary, can be null
** @node: list node, do not use outside of what is defined in this file
**
** When modifying a t_file inside of the functions given to a t_flist,
** do not modify anything but @info and @del. Use the functions defined
** below instead.
*/
typedef struct	s_file {
	t_ftype			ltype;
	t_ftype			type;
	const char		*name;
	char			*path;
	struct stat		*lstat;
	struct stat		*stat;
	void			*info;
	t_file_del		*del;
	t_dlist_node	node;
}				t_file;

/*
** Fill needed information about a file
**
** These functions return 0 in case of success, or -1 in case of error,
** setting errno appropriately.
*/
int				ls_file_lstat(t_file *file);
int				ls_file_stat(t_file *file);
int				ls_file_ltype(t_file *file);
int				ls_file_type(t_file *file);

/*
** Clear memory hold by a t_file, and make null
*/
void			ls_file_del(t_file **file);

/*
** Reinit information about a group of files
*/
typedef void	t_flist_init(void *dirinfo);

/*
** Called when inserting a file in a group
**
** This is an appropriate place to initialize the @info and @del
** members of the file.
** @dirinfo will be null if @file was a directory given on the command line.
** Must return 0 if successful, -1 otherwise.
*/
typedef int		t_flist_insert(void *dirinfo, t_file *file);

/*
** Print file information
*/
typedef void	t_flist_print(void *dirinfo, t_dlist *files);

/*
** Compare the order of two files
**
** Must return the same kind of result as strcmp to signify the order.
*/
typedef int		t_flist_compare(t_file *f1, t_file *f2);

/*
** Check whether or not a file in a dir should be printed
*/
typedef int		t_flist_reject(const char *name);

/*
** Called when an error occurs with the name of the current file
**
** It is appropriate to use errno in this type of function,
** as long as you have set before returning an error in the previous functions.
*/
typedef void	t_flist_error(const char *name);

/*
** Struct used to traverse directories
** @reverse: whether or not the ordering is reversed
** @recur: whether or not the traverse should be recursive
** @init, @insert, @prepare, @print, @compare, @reject, @error: described above
** @files: list of the next files to print
** @dirs: list of the next directories to traverse
**
** Initialize every member but @files and @list before calling ft_flist_init
** on your struct.
** @files and @dirs should not be used outside of what is defined in this file.
*/
typedef struct	s_flist {
	int				reverse;
	int				recur;
	void			*dirinfo;
	t_flist_init	*init;
	t_flist_insert	*insert;
	t_flist_print	*print;
	t_flist_compare	*compare;
	t_flist_reject	*reject;
	t_flist_error	*error;
	t_dlist			files;
	t_dlist			dirs;
}				t_flist;

/*
** Init a list
**
** Returns 0 if successful, -1 otherwise.
** This is the only function that does not call the @error member
** in case of error.
*/
int				ls_flist_init(t_flist *flist);

/*
** Add a path to the files and dirs that should be traversed
**
** Should be used at the beginning of the program with the arguments.
** In case @nofollow is not 0, will not follow symlinks.
** In case @nodirs is not 0, will not open directories.
*/
void			ls_flist_add(t_flist *flist, const char *path,
								int nofollow, int nodirs);

/*
** Should be called right after all your calls to ls_flist_add
*/
void			ls_flist_start(t_flist *flist);

/*
** Print the name of the directory and prepare the structure
** to print the files of the next directory
**
** Returns the directory or null if finished.
** ls_file_del should be called on the returned dir.
*/
t_file			*ls_flist_next(t_flist *flist,
								int (*print)(void *dirinfo, t_file *dir));

/*
** Print prepared files
**
** After ls_flist_start, will print files that were not directories.
** After ls_flist_next, will print the files of the returned directory.
** Should ALWAYS be called after each call to these two functions.
** Returns whether at least one file needed to be printed.
*/
int				ls_flist_print(t_flist *flist);

/*
** Empty the lists and free memory
**
** You are responsible to free @flist itself and its @dirinfo member.
*/
void			ls_flist_clear(t_flist *flist);

#endif
