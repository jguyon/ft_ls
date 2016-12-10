/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_format_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 22:36:24 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/09 22:36:40 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "priv/pf_utils.h"

static int	write_padding(t_stream *stream, t_pf_info *info,
							t_pf_int *arg, char *nbr)
{
	int		width;
	int		i;
	char	c;

	width = ft_strlen(arg->prefix) + ft_strlen(nbr);
	width = width < info->width ? info->width - width : 0;
	i = 0;
	c = (PF_HAS_FLAG(info->flags, PF_FLAG_ZRO)
			&& !(PF_HAS_FLAG(info->flags, PF_FLAG_NEG))
			&& info->prec < 0)
		? '0' : ' ';
	while (i < width)
	{
		ft_fputc(c, stream);
		++i;
	}
	return (i);
}

static int	write_str(t_stream *stream, char *str)
{
	ft_fputs(str, stream);
	return (ft_strlen(str));
}

int			pf_format_int(t_stream *stream, t_pf_info *info, void *arg)
{
	t_pf_int	*int_arg;
	char		*str;
	int			count;

	int_arg = (t_pf_int *)arg;
	if (!(str = ft_uimtoa_base(int_arg->n, int_arg->base,
								int_arg->upper_base, info->prec)))
		return (-1);
	if (ft_strcmp(int_arg->prefix, "0") == 0 && str[0] == '0')
		int_arg->prefix[0] = '\0';
	if (PF_HAS_FLAG(info->flags, PF_FLAG_NEG))
		count = write_str(stream, int_arg->prefix)
			+ write_str(stream, str)
			+ write_padding(stream, info, int_arg, str);
	else if (PF_HAS_FLAG(info->flags, PF_FLAG_ZRO) && info->prec < 0)
		count = write_str(stream, int_arg->prefix)
			+ write_padding(stream, info, int_arg, str)
			+ write_str(stream, str);
	else
		count = write_padding(stream, info, int_arg, str)
			+ write_str(stream, int_arg->prefix)
			+ write_str(stream, str);
	ft_memdel((void **)&str);
	return (count);
}
