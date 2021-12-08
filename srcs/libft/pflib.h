/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pflib.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:40:08 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/17 22:40:42 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_PFLIB_H
# define PRINTF_PFLIB_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include "option_flags.h"

int			calc_fill(char c, int slen, int flags[N_FLAGS], char sign);
long long	ft_ull_digits(long long n);
void		ft_putstrn(char *str, size_t n, int *char_print);
void		ft_putchari(char c, unsigned int i, int *char_print);
void		put_cc(long long n, char *s, char mod, int *char_print);
/*
**int			ft_putcharim(char c, unsigned int i);
*/
#endif
