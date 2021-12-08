/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_conversion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:00:09 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 14:00:45 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_BASE_CONVERSION_H
# define PRINTF_BASE_CONVERSION_H

# include <string.h>
# include "libft.h"
# include <stdlib.h>

int		oati(const char **onbr);
int		hati(const char **hnbr);
char	*ultha(unsigned long long n, char cap);

#endif
