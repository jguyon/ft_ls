/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_program.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 11:17:43 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/28 19:00:28 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_PROGRAM_H
# define LS_PROGRAM_H

/*
** Hooks and helpers for creating programs
*/

/*
** LS_EXIT_SUCCESS - success exit code
*/
# define LS_EXIT_SUCCESS 0

/*
** LS_EXIT_FAILURE - failure exit code
*/
# define LS_EXIT_FAILURE 1

# include <stdarg.h>

const char	*g_ls_progname;

/*
** ls_setprogname - set program name to the last part of the invocation name
** @name: invocation name of the program (argv[0])
*/
void		ls_setprogname(const char *name);

/*
** ls_getprogname - get program name
*/
const char	*ls_getprogname(void);

/*
** LS_ATEXIT_SIZE - number of exit callbacks that can be registered
*/
# define LS_ATEXIT_SIZE 32

void		(*g_ls_atexit[LS_ATEXIT_SIZE])(void);

/*
** ls_atexit - register a function to be executed by ls_exit or ls_cleanup
**
** Returns 0 if successful, -1 if not.
** Registered functions are executed in reverse order.
*/
int			ls_atexit(void (*f)(void));

/*
** ls_cleanup - clean up program before exiting
** @status: status code to return
*/
int			ls_cleanup(int status);

/*
** ls_exit - clean up program and exit
** @status: status code to exit with
*/
void		ls_exit(int status);

/*
** ls_warn - print formatted error message
** @format: message format
**
** Prints the program name, the formatted message if not null,
** and the error message given by errno.
*/
void		ls_warn(const char *format, ...);

/*
** ls_warnx - print formatted error message
** @format: message format
**
** Prints the program name followed by the formatted message if present.
*/
void		ls_warnx(const char *format, ...);

/*
** ls_err - print formatted error message and exit
** @status: status code to exit with
** @format: message format
**
** See ls_warn.
*/
void		ls_err(int status, const char *format, ...);

/*
** ls_errx - print formatted error message and exit
** @status: status code to exit with
** @format: message format
**
** See ls_warnx.
*/
void		ls_errx(int status, const char *format, ...);

/*
** va_list variants of the ls_err and ls_warn family of functions
*/
void		ls_vwarn(const char *format, va_list args);
void		ls_vwarnx(const char *format, va_list args);
void		ls_verr(int status, const char *format, va_list args);
void		ls_verrx(int status, const char *format, va_list args);

/*
** ls_getopt - extract options from program arguments
** @argc: argument count
** @argv: arguments
** @optstring: valid options
**
** Returns the next option if found, '?' if not, -1 if no more options
** are available.
** If "--" is supplied as an argument, parsing of options stops there.
*/
int			ls_getopt(int argc, char *const argv[], const char *optstring);

/*
** ls_g_optind - index of the next argument
**
** Read this variable at the end of option parsing to parse the
** rest of the arguments yourself.
*/
int			g_ls_optind;

#endif
