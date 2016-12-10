/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_close_streams.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 22:16:21 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 22:21:17 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		ls_close_streams(void)
{
	int		res;

	res = 1;
	res = ft_fclose(g_ls_stdout) ? 0 : res;
	res = ft_fclose(g_ls_stderr) ? 0 : res;
	g_ls_stdout = NULL;
	g_ls_stderr = NULL;
	return (res);
}
