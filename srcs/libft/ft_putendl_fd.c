/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 03:11:21 by sel-melc          #+#    #+#             */
/*   Updated: 2019/10/18 16:37:27 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd, int *char_print)
{
	ft_putstr_fd(s, fd, char_print);
	ft_putchar_fd('\n', fd);
}
