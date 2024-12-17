/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:07:09 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/30 11:37:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_n(char c, int fd, int amount)
{
	int	i;
	int	written;

	i = 0;
	written = 0;
	while (i < amount)
	{
		written += write(fd, &c, 1);
		i++;
	}
	return (written);
}
