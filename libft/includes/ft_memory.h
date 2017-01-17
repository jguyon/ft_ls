/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 00:20:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/17 17:52:36 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H

/*
** Memory functions
*/

# include <stddef.h>
# include <inttypes.h>
# include <limits.h>

/*
** Utilities to traverse memory using several bytes long words
** instead of one byte by one byte
*/

/*
** FT_MEM_OPT - if defined, optimize memory traversal
*/
# ifdef __APPLE__
#  define FT_MEM_OPT
# elif linux
#  define FT_MEM_OPT
# endif

/*
** FT_MEM_WORDLEN - number of bytes in a word
*/
# ifdef FT_MEM_OPT
#  if LONG_BIT == 32
#   define FT_MEM_WORDLEN 4
#  elif LONG_BIT == 64
#   define FT_MEM_WORDLEN 8
#  else
#   undef FT_MEM_OPT
#  endif
# endif

# ifdef FT_MEM_OPT

/*
** t_mem_word - type of a memory word
*/
typedef unsigned long	t_mem_word;

/*
** FT_MEM_LOBITS - word where the last bit of each byte is 1
*/
#  if FT_MEM_WORDLEN == 4
#   define FT_MEM_LOBITS 0x01010101L
#  elif FT_MEM_WORDLEN == 8
#   define FT_MEM_LOBITS 0x0101010101010101L
#  endif

/*
** FT_MEM_HIBITS - word where the first bit of each byte is 1
*/
#  if FT_MEM_WORDLEN == 4
#   define FT_MEM_HIBITS 0x80808080L
#  elif FT_MEM_WORDLEN == 8
#   define FT_MEM_HIBITS 0x8080808080808080L
#  endif

/*
** FT_MEM_WORD - word filled with a given byte
** @c: byte to repeat
*/
#  define FT_MEM_WORD(c)		((c) * FT_MEM_LOBITS)

/*
** FT_MEM_ALIGN - give the alignment offset of an address
** @p: address
**
** If used in a loop, permits to align a pointer to address which will
** permit to read words without risking to try accessing memory not
** owned by the program.
*/
#  define FT_MEM_ALIGN(p)	((uintptr_t)(p) & (FT_MEM_WORDLEN - 1))

/*
** FT_MEM_HASZERO - check if a word contains any zero byte
** @w: word to test
*/
#  define FT_MEM_HASZERO(w)	(((w) - FT_MEM_LOBITS) & ~(w) & FT_MEM_HIBITS)

# endif

/*
** ft_memalloc - allocate memory and fill it with zeros
** @size: size of the memory space to allocate
*/
void					*ft_memalloc(size_t size);

/*
** ft_memdel - free pointer and assign null to it
** @ap: address of the pointer to free
*/
void					ft_memdel(void **ap);

/*
** ft_memchr - search for a byte
** @str: memory to search in
** @c: byte to search for
** @n: maximum number of bytes to search in
*/
void					*ft_memchr(const void *str, int c, size_t n);

/*
** ft_memcmp - compare two memory spaces
** @s1: first memory space
** @s2: second memory space
** @n: maximum number of bytes to compare
**
** Returns the difference between the two last bytes which were compared
*/
int						ft_memcmp(const void *s1, const void *s2, size_t n);

/*
** ft_memset - fill a memory space with a value
** @str: memory space to fill
** @c: byte to fill @str with
** @n: number of bytes to set
*/
void					*ft_memset(void *str, int c, size_t n);

/*
** ft_bzero - fill a memory space with zeros
** @str: memory space to fill
** @n: number of bytes to fill
*/
void					ft_bzero(void *str, size_t n);

/*
** ft_memcpy - copy memory
** @dst: memory to copy into
** @src: memory to copy from
** @n: number of bytes to copy
*/
void					*ft_memcpy(void *dst, const void *src, size_t n);

/*
** ft_memccpy - copy memory up to a byte value
** @dst: memory to copy into
** @src: memory to copy from
** @c: byte value to look for
** @n: maximum number of bytes to copy
**
** Returns the address following the found byte, or null.
*/
void					*ft_memccpy(void *dst, const void *src,
									int c, size_t n);

/*
** ft_memmove - copy memory taking overlaps into account
** @dst: memory to copy into
** @src: memory to copy from
** @n: number of bytes to copy
*/
void					*ft_memmove(void *dst, const void *src, size_t n);

#endif
