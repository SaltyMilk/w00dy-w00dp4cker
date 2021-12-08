/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_display.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:58:23 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 13:59:43 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_CONV_DISPLAY_H
# define PRINTF_CONV_DISPLAY_H

# include "option_flags.h"
# include "pflib2.h"

char	display_str(char filler, int flags[N_FLAGS],
					char *s, int *char_print);

char	display_hstr(char c, int flags[N_FLAGS],
					char *s, int *char_print);

void	display_n(char filler, int flags[N_FLAGS],
					long long num, int *char_print);

void	display_char(int flags[N_FLAGS],
					char c2print, int *char_print);

char	display_ptr(char c, int flags[N_FLAGS],
					char *s, int *char_print);
#endif
