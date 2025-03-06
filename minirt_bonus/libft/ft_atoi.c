/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 18:32:09 by pipolint          #+#    #+#             */
/*   Updated: 2023/12/19 20:19:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static char	*str_op(char *str, long *flag)
{
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*flag = -1;
		str++;
	}
	return (str);
}

long	do_atoi(const char *str, long res, int flag)
{
	int		i;
	long	max;

	i = 0;
	max = LONG_MAX;
	while (ft_isdigit(str[i]))
	{
		if (((long)(str[i] - '0') > max % 10
			&& res == max / 10) || res > max / 10)
		{
			if (flag == -1)
				return (0);
			else
				return (-1);
		}
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * flag);
}

int	ft_atoi(const char *str)
{
	long	res;
	long	n_flag;

	n_flag = 1;
	str = str_op((char *)str, &n_flag);
	res = 0;
	if (*str == '-' || *str == '+')
		return (0);
	res = do_atoi(str, res, n_flag);
	return (res);
}
