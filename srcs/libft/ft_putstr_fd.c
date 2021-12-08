/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-melc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 03:07:40 by sel-melc          #+#    #+#             */
/*   Updated: 2019/10/18 16:37:34 by sel-melc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd, int *char_print)
{
	int len;

	if (!s)
		return ;
	len = ft_strlen(s);
	write(fd, s, len);
	*char_print += len;
}
