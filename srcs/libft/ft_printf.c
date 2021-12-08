/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:27:35 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/19 15:53:18 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fs, ...)
{
	va_list	a1;
	int		char_print;
	char	ret_ch;

	char_print = 0;
	va_start(a1, fs);
	while (*fs)
	{
		if (!(ret_ch = conversion_handle(&fs, a1, &char_print)))
		{
			put_cc((long long)*fs, 0, 2, &char_print);
			fs++;
		}
		else if (ret_ch == -1)
			return (-1);
	}
	va_end(a1);
	return (char_print);
}
