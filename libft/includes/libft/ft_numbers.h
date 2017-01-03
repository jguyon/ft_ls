/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyon <jguyon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/02 02:23:20 by jguyon            #+#    #+#             */
/*   Updated: 2017/01/02 02:24:31 by jguyon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NUMBERS_H
# define FT_NUMBERS_H

# include <inttypes.h>

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_uimtoa_base(uintmax_t n, unsigned int base, int upper, int prec);

#endif
