/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pflib2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 23:24:37 by sel-melc          #+#    #+#             */
/*   Updated: 2019/11/18 13:54:00 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_PFLIB2_H
# define FT_PRINTF_PFLIB2_H

# include "pflib.h"

int		special_k_calc(int flags[N_FLAGS], long long num);
void	display_num_dep(char filler, int flags[N_FLAGS],
				long long num, int *char_print);
#endif
