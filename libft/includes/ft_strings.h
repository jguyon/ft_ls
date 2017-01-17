/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 01:15:52 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 17:51:20 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRINGS_H
# define FT_STRINGS_H

/*
** String functions
*/

# include <stddef.h>

/*
** ft_strnew - allocate a string and fill it with zeros
** @size: lenth of the string to allocate
*/
char	*ft_strnew(size_t size);

/*
** ft_strdel - free a string and null its pointer
** @as - pointer to the string
*/
void	ft_strdel(char **as);

/*
** ft_strdup - duplicate a string
** @str: string to duplicate
*/
char	*ft_strdup(const char *str);

/*
** ft_strsub - create a substring of another string
** @str: string to sub
** @start: start of the substring
** @len: length of the substring
*/
char	*ft_strsub(char const *str, unsigned int start, size_t len);

/*
** ft_strjoin - concat two strings into a new one
** @s1: first string
** @s2: second string
*/
char	*ft_strjoin(char const *s1, char const *s2);

/*
** ft_strtrim - create a trimmed version of a string
** @str: string to trim
*/
char	*ft_strtrim(char const *str);

/*
** ft_strsplit - split a string
** @str: string to split
** @c: separator character
**
** Returns a null-terminated array with the splits.
*/
char	**ft_strsplit(char const *str, char c);

/*
** ft_strlen - length of a string
** @str: string to find the length of
*/
size_t	ft_strlen(const char *str);

/*
** ft_strnlen - limited length of string
** @str: string to find the length of
** @max: maximum length
*/
size_t	ft_strnlen(const char *str, size_t max);

/*
** ft_strchr - find first appearance of a character in a string
** @str: string to search in
** @c: character to search for
*/
char	*ft_strchr(const char *str, int c);

/*
** ft_strrchr - find last appearance of a character in a string
** @str: string to search in
** @c: character to search for
*/
char	*ft_strrchr(const char *str, int c);

/*
** ft_strchrnul - find character or null-character in a string
** @str: string to search in
** @c: character to search for
**
** Returns pointer to the null character of the string if nothing is found
** instead of null.
*/
char	*ft_strchrnul(const char *str, int c);

/*
** ft_strstr - find first appearance of string in another
** @big: string to search in
** @little: string to search for
*/
char	*ft_strstr(const char *big, const char *little);

/*
** ft_strnstr - find a string, stopping after a given number of characters
** @big: string to search in
** @little: string to search for
** @len: maximum number of characters to traverse
*/
char	*ft_strnstr(const char *big, const char *little, size_t len);

/*
** ft_strcmp - compare two strings
** @s1: first string
** @s2: second string
**
** Returns the difference between the last two compared characters
*/
int		ft_strcmp(const char *s1, const char *s2);

/*
** ft_strncmp - compare a number of characters in two strings
** @s1: first string
** @s2: second string
** @n: maximum number of characters to compare
*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
** ft_strequ - test equality of two strings
** @s1: first string
** @s2: second string
*/
int		ft_strequ(char const *s1, char const *s2);

/*
** ft_strnequ - test equality of a given number of characters in two strings
** @s1: first string
** @s2: second string
** @n: maximum number of characters to compare
*/
int		ft_strnequ(char const *s1, char const *s2, size_t n);

/*
** ft_strclr - fill a string with null-characters
** @str: string to clear
*/
void	ft_strclr(char *str);

/*
** ft_strcpy - copy a string
** @dst: string to copy into
** @src: string to copy from
*/
char	*ft_strcpy(char *dst, const char *src);

/*
** ft_strncpy - copy a maximum number of characters in a string
** @dst: string to copy into
** @src: string to copy from
** @len: maximum number of characters to copy, including the null character
**
** Fills the potential remaining characters with null characters
*/
char	*ft_strncpy(char *dst, const char *src, size_t len);

/*
** ft_strcat - concat a string to another
** @dst: string to concat to
** @src: string to concat
*/
char	*ft_strcat(char *dst, const char *src);

/*
** ft_strncat - append a maximum number of characters of a string to another
** @dst: string to concat to
** @src: string to concat
** @n: maximum number of characters to append
*/
char	*ft_strncat(char *dst, const char *src, size_t n);

/*
** ft_strlcat - concat a string to a buffer of a given size
** @dst: string to concat to
** @src: string to concat
** @size: size of @dst
**
** Guarentees null-termination if there is at least one free byte in @dst.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size);

#endif
