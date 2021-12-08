/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:17:26 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 13:58:13 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conv_display.h"

char	display_str(char filler, int flags[N_FLAGS],
						char *s, int *char_print)
{
	int		fill_l;

	if (!s)
		return (-1);
	fill_l = calc_fill('s', ft_strlen(s), flags, 0);
	if (flags[1] && !flags[0])
		filler = '0';
	if (!flags[0])
	{
		ft_putchari(filler, fill_l, char_print);
		if (flags[2])
			ft_putstrn(s, flags[2] - 1, char_print);
		else
			put_cc(0, s, 0, char_print);
	}
	else if (flags[0])
	{
		if (flags[2])
			ft_putstrn(s, flags[2] - 1, char_print);
		else
			put_cc(0, s, 0, char_print);
		ft_putchari(filler, fill_l, char_print);
	}
	return (1);
}

char	display_ptr(char filler, int flags[N_FLAGS], char *s, int *char_print)
{
	int fill_l;

	fill_l = calc_fill('d', ft_strlen(s) + 2, flags, 0);
	if (flags[1] && !flags[0])
		filler = '0';
	if (!flags[0])
	{
		if (filler == '0')
			put_cc(0, "0x", 0, char_print);
		ft_putchari(filler, fill_l, char_print);
		if (filler == ' ')
			put_cc(0, "0x", 0, char_print);
		if (flags[2] && (flags[2] - 1 > (int)ft_strlen(s)))
			ft_putchari('0', (flags[2] - 1) - ft_strlen(s), char_print);
		put_cc(0, (*s == '0' && flags[2] == 1) ? 0 : s, 3, char_print);
	}
	else if (flags[0])
	{
		put_cc(0, "0x", 0, char_print);
		if (flags[2] && (flags[2] - 1 > (int)ft_strlen(s)))
			ft_putchari('0', (flags[2] - 1) - ft_strlen(s), char_print);
		put_cc(0, (*s == '0' && flags[2] == 1) ? 0 : s, 3, char_print);
		ft_putchari(filler, fill_l, char_print);
	}
	return (1);
}

char	display_hstr(char filler, int flags[N_FLAGS], char *s, int *char_print)
{
	int fill_l;
	int special_k;

	if (!s)
		return (-1);
	fill_l = calc_fill('d', ft_strlen(s), flags, 0);
	if ((special_k = special_k_calc(flags, (*s - 48))) == 1)
		fill_l++;
	if (flags[1] && !flags[0] && !flags[2])
		filler = '0';
	if (!flags[0])
	{
		ft_putchari(filler, fill_l, char_print);
		if (flags[2] && (flags[2] - 1 > (int)ft_strlen(s)))
			ft_putchari('0', (flags[2] - 1) - ft_strlen(s), char_print);
		if (!special_k)
			put_cc(0, s, 3, char_print);
		return (1);
	}
	if (flags[2] && (flags[2] - 1 > (int)ft_strlen(s)))
		ft_putchari('0', (flags[2] - 1) - ft_strlen(s), char_print);
	if (!special_k)
		put_cc(0, s, 3, char_print);
	ft_putchari(filler, fill_l, char_print);
	return (1);
}

void	display_n(char filler, int flags[N_FLAGS]
		, long long num, int *char_print)
{
	if (flags[1] && !flags[0] && !flags[2])
		filler = '0';
	if (num < 0 && filler == '0')
		put_cc('-', 0, 2, char_print);
	display_num_dep(filler, flags, num, char_print);
}

void	display_char(int flags[N_FLAGS], char c2print, int *char_print)
{
	char	filler;
	int		fill_l;

	filler = ' ';
	fill_l = calc_fill('c', 1, flags, 0);
	if (flags[1] && !flags[0])
		filler = '0';
	if (!flags[0])
	{
		ft_putchari(filler, fill_l, char_print);
		put_cc(c2print, 0, 2, char_print);
	}
	else if (flags[0])
	{
		put_cc(c2print, 0, 2, char_print);
		ft_putchari(filler, fill_l, char_print);
	}
}
