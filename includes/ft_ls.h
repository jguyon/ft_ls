/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 12:03:15 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 17:47:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "libftstream.h"
# include "libftprintf.h"

typedef struct	s_ls_args {
	char		*cmd;
	t_list		*files;
}				t_ls_args;

t_ls_args		*ls_parse_args(int ac, char **av);
void			ls_destroy_args(t_ls_args **args);

#endif
