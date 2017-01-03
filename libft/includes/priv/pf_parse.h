/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 03:38:31 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 03:52:14 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PF_PARSE_H
# define PF_PARSE_H

# include <stdarg.h>
# include "libft/ft_lists.h"
# include "libft/ft_streams.h"
# include "priv/pf_info.h"

typedef struct	s_pf_format {
	char	spec;
	void	*(*get_arg)(t_pf_info *info, va_list ap);
	int		(*format)(t_stream *stream, t_pf_info *info, void *arg);
	void	(*clean_arg)(void **arg);
}				t_pf_format;

typedef struct	s_pf_conv {
	const char			*prev;
	size_t				len;
	t_pf_info			*info;
	t_pf_format			*format;
	void				*arg;
}				t_pf_conv;

typedef struct	s_pf_conv_acc {
	int			count;
	t_stream	*stream;
}				t_pf_conv_acc;

typedef struct	s_pf_arg {
	size_t		n;
	t_pf_conv	*conv;
	int			type;
}				t_pf_arg;

t_list			*pf_parse_format(const char *format);
int				pf_extract_args(t_list *convs, va_list ap);
int				pf_write_convs(t_stream *stream, t_list *convs);
void			pf_del_convs(t_list **convs);

t_pf_info		*pf_get_info(char **format);
t_pf_format		*pf_get_format(t_pf_info *info);

#endif
