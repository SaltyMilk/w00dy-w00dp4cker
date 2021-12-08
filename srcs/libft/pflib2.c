/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pflib2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:35:33 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 13:53:42 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pflib2.h"

/*
** This function helps fix issue with
** %.0d %N.d, ...
*/

int		special_k_calc(int flags[N_FLAGS], long long num)
{
	int special_k;

	special_k = 0;
	if (!num && flags[2] == 1 && flags[3])
		special_k = 1;
	else if (!num && flags[2] == 1 && !flags[3])
		special_k = 2;
	return (special_k);
}

void	display_num_dep(char filler, int flags[N_FLAGS],
						long long num, int *char_print)
{
	int	fill_l;

	fill_l = calc_fill('d', ft_ull_digits(num), flags, (num < 0) ? 1 : 0);
	if (special_k_calc(flags, num) == 1)
		fill_l++;
	if (!flags[0])
	{
		ft_putchari(filler, fill_l, char_print);
		if (num < 0 && filler != '0')
			put_cc('-', 0, 2, char_print);
		if (flags[2] && (flags[2] - 1 > ft_ull_digits(num)))
			ft_putchari('0', (flags[2] - 1) - ft_ull_digits(num), char_print);
		if (!special_k_calc(flags, num))
			put_cc(num, 0, 1, char_print);
	}
	else if (flags[0])
	{
		if (num < 0 && filler != '0')
			put_cc('-', 0, 2, char_print);
		if (flags[2] && (flags[2] - 1 > ft_ull_digits(num)))
			ft_putchari('0', (flags[2] - 1) - ft_ull_digits(num), char_print);
		if (!special_k_calc(flags, num))
			put_cc(num, 0, 1, char_print);
		ft_putchari(filler, fill_l, char_print);
	}
}
