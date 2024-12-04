/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:55:28 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 10:51:47 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_minirt *m, char *str)
{
	int		i;
	char	**strs;

	if (m->ambient->flag != 0)
		parse_error(m, "Error: Ambient: You can only have one", str, NULL);
	else
		m->ambient->flag = 1;
	strs = ft_split_and_check(m, str, ' ', true);
	i = 1;
	if (arr_len(strs) != 3)
		parse_error(m, "Error: Ambient: Invalid number of arguments", \
			str, strs);
	while (str && str[i])
	{
		if (i == 1 && check_double(strs[i], &m->ambient->ratio, false))
			parse_error(m, "Error: Ambient: Invalid ambient ratio", str, strs);
		if (i == 2 && dovectorcolor(strs[i], &m->ambient->color) == false)
			parse_error(m, "Error: Ambient: Invalid ambient color", str, strs);
		i++;
	}
	free_arr(strs);
	scalar(&m->ambient->color, m->ambient->ratio);
	return (0);
}

int	parse_cone(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**strs;
	double	height;

	strs = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if (arr_len(strs) < 5 || arr_len(strs) > 9)
		parse_error(m, "Error: Cone: Invalid number of arguments", str, strs);
	m->shapes[*j] = alloc_shape(m);
	while (strs && strs[i++])
	{
		if (i == 1 && !dovector(strs[i], &m->shapes[*j]->coords, false))
			parse_error(m, "Error: Invalid cone coordinates", str, strs);
		if (i == 2 && !dovector(strs[i], &m->shapes[*j]->orientation, true))
			parse_error(m, "Error: Invalid cone orientation", str, strs);
		if (i == 3 && check_radius(m->shapes[*j], strs[i], &height))
			parse_error(m, "Error: Invalid cone height", str, strs);
		if (i == 4 && !dovectorcolor(strs[i], &m->shapes[*j]->material->color))
			parse_error(m, "Error: Invalid cone color", str, strs);
		if (i == 5 && parse_bonus_specs(m, m->shapes[*j]->material, &strs[i]))
			return (1);
	}
	free_arr(strs);
	m->shapes[*j]->h = height;
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
		if (res / 2 < 0 || res < 0)
			return (1);	
		shape->h = res / 2;
		return (0);
	}
	*num = str_to_double(str);
	if (*num / 2 < 0 || *num < 0)
		return (1);
	shape->h = (*num) / 2;
	return (0);
}

int	parse_light(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;

	str = ft_split_and_check(m, string, ' ', true);
	i = 1;
	if (arr_len(str) != 4)
		parse_error(m, "Error: Light: Invalid number of arguments", \
			string, str);
	m->lights[*j] = ft_calloc(1, sizeof(t_light));
	while (str && str[i])
	{
		if (i == 1 && !dovector(str[i], &m->lights[*j]->position, false))
			parse_error(m, "Error: Light: Invalid coordinates", string, str);
		if (i == 2 && check_double(str[i], &m->lights[*j]->brightness, true))
			parse_error(m, "Error: Light: Invalid brightness ratio", \
				string, str);
		if (i == 3 && !dovectorcolor(str[i], &m->lights[*j]->intensity))
			parse_error(m, "Error: Light: Invalid color", string, str);
		i++;
	}
	free_arr(str);
	m->light_count++;
	*j += 1;
	return (0);
}
