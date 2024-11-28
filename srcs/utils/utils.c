/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:29:54 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/28 19:34:25 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_err(char *err, char need_newline)
{
	if (write(2, err, ft_strlen(err)) == -1)
		return ;
	if (need_newline != '\0')
	{
		if (write(2, "\n", 1) == -1)
			return ;
	}
}

double	str_to_double(char *str)
{
	double	sum;
	double	prec;
	double	div;
	double	sign;

	prec = 0;
	div = 1.0;
	sign = 1.0;
	if (str && str[0] == '-')
		sign *= -1.0;
	sum = (double)ft_atoi(str);
	while (*str && *str != '.')
		str++;
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			div *= 10;
			prec += (*str - '0') / div;
			str++;
		}
		sum += prec * sign;
	}
	return (sum);
}

int	is_double(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i])
	{
		if (ft_isdigit(str[i]) != 1 && str[i] != '-' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

int	arr_len(char *arr[])
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

void	free_arr(char *arr[])
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}
