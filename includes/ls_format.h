/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:00:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/13 21:29:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_FORMAT_H
# define LS_FORMAT_H

/*
** Format and output file information
*/

# include <sys/stat.h>
# include <stddef.h>

/*
** Structure holding file info used for the long format
*/
typedef struct	s_finfo {
	char		mode[11];
	char		nlinks[sizeof(nlink_t) * 3 + 1];
}				t_finfo;

/*
** Set mode string in @info from @st
*/
void			ls_set_mode(t_finfo *info, struct stat *st);

/*
** Set number of links string in @info from @st
**
** Returns the length of the string.
*/
size_t			ls_set_nlinks(t_finfo *info, struct stat *st);

#endif
