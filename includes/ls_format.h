/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_format.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/13 17:00:30 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/13 18:33:57 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_FORMAT_H
# define LS_FORMAT_H

/*
** Format and output file information
*/

# include <sys/stat.h>

/*
** Structure holding file info used for the long format
*/
typedef struct	s_finfo {
	char		mode[11];
}				t_finfo;

/*
** Set mode string in @info from @st
*/
void			ls_set_mode(t_finfo *info, struct stat *st);

#endif
