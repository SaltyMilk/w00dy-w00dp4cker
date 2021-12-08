/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:00:51 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 20:06:54 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base_conversion.h"

/*
** Note : oati and hati are not needed
**        because C language handles
**        escape seq. chars
** Functions kept though for later use
*/

int		oati(const char **onbr)
{
	int	i;
	int	digits;
	int	nbr;

	nbr = 0;
	i = 0;
	digits = 0;
	while (ft_isdigit((*onbr)[digits]) && digits < 3)
		digits++;
	while (i < digits)
	{
		nbr += ((*onbr)[i] - 48) * ft_pow(8, digits - i - 1);
		i++;
	}
	*onbr += digits - 1;
	return (nbr);
}

int		hati(const char **hnbr)
{
	size_t	i;
	size_t	digits;
	int		nbr;

	i = 0;
	nbr = 0;
	digits = 0;
	(*hnbr)++;
	while (**hnbr == '0')
		(*hnbr)++;
	while ((ft_isdigit(**hnbr) || (**hnbr >= 'a' && **hnbr <= 'f')
				|| (**hnbr >= 'A' && **hnbr <= 'F')) && digits < 2)
		digits++;
	while (i < digits)
	{
		nbr += ((*hnbr)[i] - 48) * ft_pow(16, digits - i - 1);
		i++;
	}
	*hnbr += digits - 1;
	return (nbr);
}

/*
** cap 0 = none-capital letters
** cap 1 = capital letters
*/

char	*ultha(unsigned long long n, char cap)
{
	const char			*hexset;
	char				*hstr;
	int					hexdigits;
	unsigned long long	inbr;

	if (!n)
		return (ft_strdup("0"));
	hexset = "0123456789ABCDEF";
	if (!cap)
		hexset = "0123456789abcdef";
	hexdigits = 0;
	inbr = n;
	while ((n = n / 16))
		hexdigits++;
	hexdigits++;
	if (!(hstr = ft_calloc((hexdigits + 1),sizeof(char))))
		return (NULL);
	hstr[hexdigits] = 0;
	while (hexdigits--)
	{
		hstr[hexdigits] = hexset[inbr % 16];
		inbr /= 16;
	}
	return (hstr);
}
