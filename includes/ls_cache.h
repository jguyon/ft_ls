/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_cache.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 21:24:38 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/15 00:15:51 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_CACHE_H
# define LS_CACHE_H

/*
** Cache mechanism using dlists
*/

# include "ft_dlists.h"

/*
** Helper to easily initialize the dlist of t_cache
**
** Should be move to ft_dlists.h.
*/
# define LS_DLST(n, t, m) {FT_DLST_OFFSET(t, m), {&(n.head), &(n.head)}}

/*
** Check if @entry corresponds to @val
*/
typedef int		t_cache_is(void *entry, void *val);

/*
** Create an entry from @val when not present in the cache
*/
typedef void	*t_cache_new(void *val);

/*
** Frees memory of an @entry when removing it from the cache
*/
typedef void	t_cache_del(void *entry);

/*
** Cache type
** @is, @new, @del: functions used to check, create or delete entries
** @list: a dlist of the type of the values you want to cache
*/
typedef struct	s_cache {
	t_cache_is	*is;
	t_cache_new	*new;
	t_cache_del	*del;
	t_dlist		list;
}				t_cache;

/*
** Find the entry corresponding to @val in @cache, or create it
*/
void			*ls_cache_get(t_cache *cache, void *val);

/*
** Empty @cache and free each of its entries
*/
void			ls_cache_clear(t_cache *cache);

#endif
