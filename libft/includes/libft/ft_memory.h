/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 00:20:48 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/03 12:24:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMORY_H
# define FT_MEMORY_H

# include <stddef.h>
# include <inttypes.h>

# define FT_MEM_WORDLEN		8
# define FT_MEM_LOBITS		0x0101010101010101
# define FT_MEM_HIBITS		0x8080808080808080
# define FT_MEM_WORD(c)		((c) * FT_MEM_LOBITS)
# define FT_MEM_ALIGN(p)	((uintptr_t)(p) & 7)
# define FT_MEM_HASZERO(w)	(((w) - FT_MEM_LOBITS) & ~(w) & FT_MEM_HIBITS)

typedef uint64_t	t_mem_word;

void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);

void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memset(void *str, int c, size_t len);
void				ft_bzero(void *str, size_t n);

void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);

#endif
