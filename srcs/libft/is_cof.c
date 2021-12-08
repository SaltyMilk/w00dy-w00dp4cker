/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cof.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:14:47 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/17 22:16:47 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is_cof.h"

/*
** This file defines which conversions and flags are handled
*/

char	is_conversion(char c)
{
	if (c == 's' || c == 'd' || c == '%' || c == 'u'
			|| c == 'c' || c == 'x' || c == 'X' || c == 'p'
			|| c == 'd' || c == 'i' || c == 'l')
		return (1);
	return (0);
}

char	is_flag(char c)
{
	if (c == '.' || c == '0' || c == '*' || c == '-')
		return (1);
	return (0);
}
