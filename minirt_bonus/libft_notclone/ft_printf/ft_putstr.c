/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:20:52 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/30 11:37:35 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *str, int fd, int n)
{
	int	written;
	int	s;

	written = 0;
	s = 0;
	written += write(fd, &str[s], n);
	return (written);
}
