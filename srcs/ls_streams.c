/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_streams.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 22:22:57 by jguyon            #+#    #+#             */
/*   Updated: 2016/12/10 22:54:33 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			g_ls_stdout_fd = LS_DEFAULT_STDOUT;
int			g_ls_stderr_fd = LS_DEFAULT_STDERR;
t_stream	*g_ls_stdout = NULL;
t_stream	*g_ls_stderr = NULL;
char		*g_ls_progname = LS_DEFAULT_PROGNAME;
