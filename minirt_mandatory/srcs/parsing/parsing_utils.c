/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:48:18 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 14:46:35 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	is_in_bounds(t_tuple *vector, t_bool for_color)
{
	if (for_color)
	{
		if (vector->x > 1 || vector->x < 0)
			return (false);
		if (vector->y > 1 || vector->y < 0)
			return (false);
		if (vector->z > 1 || vector->z < 0)
			return (false);
		return (true);
	}
	if (vector->x > 1 || vector->x < -1)
		return (false);
	if (vector->y > 1 || vector->y < -1)
		return (false);
	if (vector->z > 1 || vector->z < -1)
		return (false);
	return (true);
}

t_bool	dovector(t_minirt *m, char *string, t_tuple *vec, t_bool should_norm)
{
	char	**str;
	int		i;

	i = -1;
	str = ft_split(string, ',');
	while (str && str[++i])
	{
		if (!is_double(str[i]) && free_arr(str))
			return (false);
	}
	if (arr_len(str) != 3 && free_arr(str))
		return (false);
	else
	{
		vec->x = str_to_double(str[0]);
		vec->y = str_to_double(str[1]);
		vec->z = str_to_double(str[2]);
	}
	if (should_norm == true && check_magnitude(m, vec, string) && free_arr(str))
	{
		normalize(vec);
		return (is_in_bounds(vec, false));
	}
	free_arr(str);
	return (true);
}

t_bool	dovectorcolor(char *string, t_tuple *calc)
{
	char	**str;
	int		i;

	i = -1;
	str = ft_split(string, ',');
	while (str && str[++i])
	{
		if (!is_double(str[i]))
		{
			free_arr(str);
			return (false);
		}
	}
	if (arr_len(str) != 3 && free_arr(str))
		return (false);
	calc->x = str_to_double(str[0]) / 255.0;
	calc->y = str_to_double(str[1]) / 255.0;
	calc->z = str_to_double(str[2]) / 255.0;
	free_arr(str);
	return (is_in_bounds(calc, true));
}

int	check_ulong(char *str, double *num)
{
	if (!isulong(str))
		return (1);
	*num = ft_atoi(str);
	if (*num > 180 || *num < 0)
		return (1);
	return (0);
}

int	check_double(char *str, double *num, t_bool check_boundary)
{
	if (!is_double(str))
		return (1);
	*num = str_to_double(str);
	if (check_boundary == true)
	{
		if (*num > 1 || *num < 0)
			return (1);
	}
	return (0);
}
