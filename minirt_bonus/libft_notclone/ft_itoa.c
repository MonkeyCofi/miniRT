/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:46:04 by pipolint          #+#    #+#             */
/*   Updated: 2023/11/05 12:15:03 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digit_count(int n)
{
	int	digits;

	digits = 1;
	if (n < 0)
		digits++;
	while (n / 10)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*str;
	int		i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	digits = digit_count(n);
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (NULL);
	i = digits - 1;
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		if (n < 0)
		{
			str[0] = '-';
			n *= -1;
		}
		str[i--] = (n % 10) + 48;
		n /= 10;
	}
	str[digits] = '\0';
	return (str);
}
