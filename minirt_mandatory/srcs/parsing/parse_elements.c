/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:55:28 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 19:38:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_minirt *m, char *str)
{
	int		i;
	char	**strs;

	if (m->ambient->flag != 0 && free_str(str))
		parse_error(m, "Ambient: You can only have one", NULL, 1);
	m->ambient->flag = 1;
	strs = ft_split_and_check(m, str, ' ', true);
	i = 1;
	if (arr_len(strs) != 3 && free_str(str))
		parse_error(m, "Ambient: Invalid number of arguments", strs, 1);
	while (str && str[i])
	{
		if (i == 1 && check_double(strs[i], &m->ambient->ratio, true) \
			&& free_str(str))
			parse_error(m, "Ambient: Invalid ambient ratio", strs, 1);
		if (i == 2 && !dovectorcolor(strs[i], &m->ambient->color) \
			&& free_str(str))
			parse_error(m, "Ambient: Invalid ambient color", strs, 1);
		i++;
	}
	free_arr(strs);
	scalar(&m->ambient->color, m->ambient->ratio);
	return (0);
}

int	check_height(t_shape *shape, char *str, double *num)
{
	double	res;

	if (!is_double(str))
		return (1);
	if (!num)
	{
		res = str_to_double(str);
		if (res < 0 || res < 0)
			return (1);
		shape->h = res;
		return (0);
	}
	*num = str_to_double(str);
	if (*num < 0 || *num < 0)
		return (1);
	shape->h = (*num);
	return (0);
}

int	parse_light(t_minirt *m, char *string)
{
	int		i;
	char	**str;

	if (m->light->found != 0 && free_str(string))
		parse_error(m, "Light: You can only have one", NULL, 1);
	else
		m->light->found = 1;
	str = ft_split_and_check(m, string, ' ', true);
	i = 0;
	if (arr_len(str) != 4 && free_str(string))
		parse_error(m, "Light: Invalid number of arguments", str, 1);
	while (str && str[i++])
	{
		if (i == 1 && !dovector(m, str[i], &m->light->position, false) \
			&& free_str(string))
			parse_error(m, "Light: Invalid coordinates", str, 1);
		if (i == 2 && check_double(str[i], &m->light->brightness, true) \
			&& free_str(string))
			parse_error(m, "Light: Invalid brightness ratio", str, 1);
		if (i == 3 && !dovectorcolor(str[i], &m->light->intensity) \
			&& free_str(string))
			parse_error(m, "Light: Invalid color", str, 1);
	}
	free_arr(str);
	return (0);
}
