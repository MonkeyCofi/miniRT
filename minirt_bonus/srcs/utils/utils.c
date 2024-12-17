/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 07:29:54 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 18:44:53 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_magnitude(t_minirt *m, t_tuple *vector, char *line)
{
	if (is_equal(magnitude(vector), 0))
		return (0);
	if (is_equal(magnitude(vector), 1) == false)
	{
		write_check(m, "Line: ");
		write_check(m, line);
		write_check(m, " is not normalized\n");
		write_check(m, "Normalizing vector\n");
	}
	return (1);
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

int	free_arr(char *arr[])
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
	return (1);
}
