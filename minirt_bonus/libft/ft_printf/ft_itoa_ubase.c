/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_ubase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:06:36 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/24 17:59:55 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	return_based_length(unsigned long n, int base)
{
	size_t	digits;

	digits = 1;
	if (n == 0)
		return (1);
	while (n / base)
	{
		digits++;
		n /= base;
	}
	return (digits);
}

char	*ft_itoa_ubase(unsigned long n, char *base)
{
	size_t	base_l;
	size_t	length;
	char	*str;
	int		digit;

	base_l = ft_strlen(base);
	length = return_based_length(n, base_l);
	str = ft_calloc(length + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		digit = n % base_l;
		str[--length] = base[digit];
		n /= base_l;
	}
	return (str);
}
