/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 03:14:48 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/17 23:23:47 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_ndigits(long long n)
{
	int digits;

	digits = 0;
	if (!n)
		return (1);
	while (n >= 1)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

static	int	ft_powa(long long n, unsigned int pow)
{
	if (pow == 0)
		return (1);
	else if (pow == 1)
		return (n);
	return (n * ft_powa(n, pow - 1));
}

void		ft_putnbr_fd(long long n, int fd)
{
	int i;

	if (n < 0)
		n *= -1;
	i = get_ndigits(n);
	while (i > 0)
	{
		ft_putchar_fd((((n / (ft_powa(10, i - 1))) % 10) + 48), fd);
		i--;
	}
}
