/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_tty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:51:01 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/23 13:11:07 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_TTY_H
# define LS_TTY_H

/*
** Utils to get information about the terminal
*/

# include <stddef.h>

/*
** File descriptor of the terminal
*/
# define LS_TTY_FD 1

/*
** Terminal width to assume if not possible to get it
*/
# define LS_TTY_DEFAULT_WIDTH 80

/*
** Get terminal width
*/
size_t	ls_tty_width(void);

#endif
