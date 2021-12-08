/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pflib.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:37:16 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/17 22:40:00 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pflib.h"

/*
** sign == 1 : n is negatif
*/

int			calc_fill(char c, int slen, int flags[N_FLAGS], char sign)
{
	int	displayed_c;

	if (c == 's' && flags[2] - 1 > slen)
		flags[2] = slen + 1;
	else if (c == 'd')
	{
		if (flags[2] - 1 > slen)
			displayed_c = flags[2] - 1;
		else
			displayed_c = slen;
		slen = displayed_c + sign;
	}
	if (flags[2] && c == 's')
		return ((flags[3] > (flags[2] - 1)) ? (flags[3] - (flags[2] - 1)) : 0);
	else
		return ((flags[3] > slen) ? (flags[3] - slen) : 0);
}

long long	ft_ull_digits(long long n)
{
	int digits;

	digits = 0;
	if (!n)
		return (1);
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

void		ft_putstrn(char *str, size_t n, int *char_print)
{
	if (!str)
		return ;
	write(1, str, n);
	*char_print += n;
}

/*
**  This version is less optimized
**  multiple write's but doesn't malloc
*/

void		ft_putchari(char c, unsigned int i, int *char_print)
{
	*char_print += i;
	while (i--)
		write(1, &c, 1);
}

/*
** returns 0 on error
*/
/*
**int ft_putcharim(char c, unsigned int i)
**{
**	char			*s;
**	unsigned int	j;
**
**	j = 0;
**	if (!(s = malloc(sizeof(char) * i + 1)))
**		return (0);
**	while (j < i)
**		s[j++] = c;
**	s[j] = 0;
**	write(1, s, i);
**	free(s);
**	return (1);
**}
*/
/*
** mod = 0 : putstr | g_cc + strlen
** mod = 1 : putnbr | g_cc + ull_digits
** mod = 2 : putchar| g_cc++
** mod = 3 : putstr & free | g_cc + strlen
*/

void		put_cc(long long n, char *s, char mod, int *char_print)
{
	if (!mod)
		ft_putstr_fd(s, 1, char_print);
	else if (mod == 1)
	{
		ft_putnbr_fd(n, 1);
		*char_print += ft_ull_digits(n);
	}
	else if (mod == 2)
	{
		ft_putchar_fd(n, 1);
		(*char_print)++;
	}
	else if (mod == 3)
	{
		if (!s)
			return ;
		ft_putstr_fd(s, 1, char_print);
		free(s);
	}
}
