/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_futils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 21:02:16 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 21:13:37 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_futils.h"

/*
** CONV :
** 0 = not a conversion
** 'c' = %c | 's' = %s | 'd' = %d ...
** note if 0 < ret <= 4 : nbr flags used
** - 0 . * |
** last flag is always : minimum field
*/
typedef unsigned long	t_ul;
typedef unsigned int	t_ui;

char	str_is_conv(const char **s, va_list a1, int flags[N_FLAGS])
{
	size_t	i;

	if (!**s || **s != '%')
		return (0);
	i = 1;
	ft_bzero(flags, sizeof(int) * (N_FLAGS));
	i += count_flags(*s + 1, flags, a1);
	*s += i;
	if (!**s || !is_conversion(**s))
		return (0);
	else
		return (**s);
}

void	str_handle(char c, va_list a1, int flags[N_FLAGS], int *char_print)
{
	char	*s;

	if (c == 's')
	{
		if (!(s = va_arg(a1, char *)))
			s = "(null)";
		display_str(' ', flags, s, char_print);
	}
}

char	conversion_handle(const char **fs, va_list a, int *char_print)
{
	char	c;
	int		flags[N_FLAGS];

	if (!(c = str_is_conv(fs, a, flags)))
		return (0);
	(*fs)++;
	str_handle(c, a, flags, char_print);
	if (c == 'd' || c == 'i')
		display_n(' ', flags, va_arg(a, int), char_print);
	else if (c == 'u')
		display_n(' ', flags, va_arg(a, t_ui), char_print);
	else if (c == 'c')
		display_char(flags, va_arg(a, t_ui), char_print);
	else if (c == '%')
		display_char(flags, (t_ui)'%', char_print);
	else if (c == 'x')
		return (display_hstr(' ', flags,
				ultha(va_arg(a, t_ui), 0), char_print));
	else if (c == 'l')
		return (display_hstr(' ', flags,
				ultha(va_arg(a, unsigned long int), 0), char_print));
	else if (c == 'X')
		return (display_hstr(' ', flags,
				ultha(va_arg(a, t_ui), 1), char_print));
	else if (c == 'p')
		return (display_ptr(' ', flags, ultha(va_arg(a, t_ul), 0), char_print));
	return (1);
}

/*
** Returns corresponding char
** or 0 to signal none-bs char
** REALIZED c handles escape sequence
** So this is obsolete but will keep it
** as comment just in case
**
**
**char bs_char_handle(const char **fs, int *char_print)
**{
**if (**fs != 92)
**       return (0);
**   (*fs)++;
**  if (**fs == 'a')
**       return (7);
**   else if (**fs == 'b')
**       return (8);
**   else if (**fs == 'f')
**      return (12);
**   else if (**fs == 'n')
**       return (10);
**   else if (**fs == 'r')
**       return (13);
**   else if (**fs == 't')
**       return (9);
**   else if (**fs == 'v')
**       return (11);
**   else if (**fs == 39 || **fs == 92 || **fs == 34 || **fs == 63)
**       return (**fs);
**   else if (ft_isdigit(**fs))
**       return (oati(fs));
**   else if (**fs == 'x')
**       return (hati(fs));
**   return (0);
**}
*/
