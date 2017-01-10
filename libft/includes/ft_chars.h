/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 02:16:04 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 12:27:41 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CHARS_H
# define FT_CHARS_H

/*
** Character functions
*/

/*
** ft_isalpha - check if a character is a letter
** @c: character to test
*/
int		ft_isalpha(int c);

/*
** ft_isdigit - check if a character is a decimal digit
** @c: character to test
*/
int		ft_isdigit(int c);

/*
** ft_isalnum - check if a character is a letter or a decimal digit
** @c: character to test
*/
int		ft_isalnum(int c);

/*
** ft_isascii - check if a character is in ascii
** @c: character to test
*/
int		ft_isascii(int c);

/*
** ft_isprint - check if character is printable
** @c: character to test
*/
int		ft_isprint(int c);

/*
** ft_toupper - convert character to its uppercase version
** @c: character to test
*/
int		ft_toupper(int c);

/*
** ft_tolower - convert character to its lowercase version
** @c: character to test
*/
int		ft_tolower(int c);

#endif
