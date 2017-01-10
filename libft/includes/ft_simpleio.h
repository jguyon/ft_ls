/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simpleio.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 02:30:35 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 12:39:43 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SIMPLEIO_H
# define FT_SIMPLEIO_H

/*
** Simple output functions
*/

/*
** ft_putchar - print a character to stdout
** @c: character to print
*/
void	ft_putchar(char c);

/*
** ft_putstr - print a string to stdout
** @str: string to print
*/
void	ft_putstr(char const *str);

/*
** ft_putendl - print a string followed by a newline to stdout
** @str: string to print
*/
void	ft_putendl(char const *str);

/*
** ft_putnbr - print an int to stdout
** @n: int to print
*/
void	ft_putnbr(int n);

/*
** ft_putchar_fd - print a character to a file
** @c: character to print
** @fd: file descriptor
*/
void	ft_putchar_fd(char c, int fd);

/*
** ft_putstr_fd - print a string to a file
** @str: string to print
** @fd: file descriptor
*/
void	ft_putstr_fd(char const *str, int fd);

/*
** ft_putendl_fd - print a string followed by a newline to a file
** @str: string to print
** @fd: file descriptor
*/
void	ft_putendl_fd(char const *str, int fd);

/*
** ft_putnbr_fd - print an int to a file
** @n: int to print
** @fd: file descriptor
*/
void	ft_putnbr_fd(int n, int fd);

#endif
