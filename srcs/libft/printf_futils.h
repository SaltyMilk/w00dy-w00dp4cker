/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_futils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 22:14:03 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 16:06:22 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_PRINTF_FUTILS_H
# define PRINTF_PRINTF_FUTILS_H

# include "base_conversion.h"
# include "is_cof.h"
# include "conv_display.h"

char str_is_conv(const char **str, va_list a1, int flags[N_FLAGS]);
char conversion_handle(const char **fs, va_list a1, int *char_print);

#endif
