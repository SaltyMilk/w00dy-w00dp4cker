/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_flags.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:52:56 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 13:53:17 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_OPTION_FLAGS_H
# define PRINTF_OPTION_FLAGS_H

# define N_FLAGS 4
# include <stdarg.h>
# include "libft.h"
# include "is_cof.h"
# include "pflib.h"

char	count_flags(const char *s, int flags[N_FLAGS], va_list a1);
#endif
