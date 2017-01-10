/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unicode.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 02:37:50 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/08 20:11:55 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UNICODE_H
# define FT_UNICODE_H

/*
** DEPRECATED - needs rewrite
*/

# define FT_WC_MAXBYTES 4

# include <wchar.h>

size_t	ft_wcconv(char *dst, wchar_t wc);
size_t	ft_wclen(wchar_t wc);
size_t	ft_wstrlen(const wchar_t *ws);

#endif
