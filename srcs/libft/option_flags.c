/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:47:34 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 13:52:46 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option_flags.h"

int		zero_before_num(const char *s)
{
	int i;

	i = 0;
	while (s[i] && ft_isdigit(s[i]))
	{
		if (s[i] != '0')
			return (i);
		i++;
	}
	return (0);
}

/*
** 0->HANDLED_FLAGS
** 0 1 2      3
** - 0 . (*) 'N'
**
** Note :
** flags[4](*)==1 => will be used to determine last flag
** flags[4](*)==2 => will be used to determine precision
**
** Note : flags[2](.) = 0 when not active or has
** a value of "precision - 1" (so flags[2] == 1)
** => means precision of 0
*/

void	set_flags(char const *s, int flags[N_FLAGS], int *i,
					va_list a1)
{
	if (s[*i] == '-')
		flags[0] = 1;
	else if (s[*i] == '0')
		flags[1] = 1;
	else if (s[*i] == '.')
	{
		if (s[*i + 1] == '*')
		{
			flags[2] = va_arg(a1, int) + 1;
			(*i)++;
		}
		else if (((flags[2] = ft_atoi(s + *i + 1)) || s[(*i) + 1] == '0'))
			*i += ft_ull_digits(flags[2]++) + zero_before_num(s + *i + 1);
		else
			flags[2]++;
	}
	else if (s[*i] == '*')
		flags[3] = va_arg(a1, int);
	else if (ft_isdigit(s[*i]))
		if ((flags[3] = ft_atoi(s + *i)))
			*i += ft_ull_digits(flags[3]) - 1;
	if (flags[2] < 0)
		flags[2] = 0;
	if (flags[3] < 0 && (flags[0] = 1))
		flags[3] *= -1;
}

char	count_flags(const char *s, int flags[N_FLAGS],
					va_list a1)
{
	int	i;

	i = 0;
	while (is_flag(s[i]) || ft_isdigit(s[i]))
	{
		if ((((!(s[i] == '-' && flags[0]) || !(s[i] == '0' && flags[1]) ||
			!(s[i] == '.' && flags[2]) || !(s[i] == '*' && flags[3]))) &&
			is_flag(s[i])) || ft_isdigit(s[i]))
			set_flags(s, flags, &i, a1);
		i++;
	}
	if (flags[2] < 0)
		flags[2] *= -1;
	if (flags[3] < 0)
		flags[3] *= -1;
	return (i);
}
