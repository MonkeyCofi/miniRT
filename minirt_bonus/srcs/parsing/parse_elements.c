/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:55:28 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 20:56:09 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_camera(t_minirt *minirt, char *string)
{
	char	**str;
	int		i;

	i = 0;
	if (minirt->cam->flag != 0 && free_str(string))
		parse_error(minirt, CAM_AMT_ERR, NULL, 1);
	minirt->cam->flag = 1;
	str = ft_split(string, ' ');
	if (arr_len(str) != 4 && free_str(string))
		parse_error(minirt, CAM_ARG_ERR, str, 1);
	while (str[i] && str[i++])
	{
		if (i == 1 && !dovector(minirt, str[i], &minirt->from, false) \
			&& free_str(string))
			parse_error(minirt, CAM_COORD_ERR, str, 1);
		if (i == 2 && !dovector(minirt, str[i], &minirt->to, true) \
			&& free_str(string))
			parse_error(minirt, CAM_ORIENT_ERR, str, 1);
		if (i == 3 && check_ulong(str[i], &minirt->cam->fov) \
			&& free_str(string))
			parse_error(minirt, "Error\nCamera: Invalid FOV", str, 1);
		minirt->from.w = POINT;
	}
	free_arr(str);
	return (0);
}

int	parse_ambient(t_minirt *m, char *str)
{
	int		i;
	char	**strs;

	if (m->ambient->flag != 0 && free_str(str))
		parse_error(m, "Ambient: You can only have one", NULL, 1);
	m->ambient->flag = 1;
	strs = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if (arr_len(strs) != 3 && free_str(str))
		parse_error(m, "Ambient: Invalid number of arguments", strs, 1);
	while (str && str[i++])
	{
		if (i == 1 && check_double(strs[i], &m->ambient->ratio, true) \
			&& free_str(str))
			parse_error(m, "Ambient: Invalid ambient ratio", strs, 1);
		if (i == 2 && !dovectorcolor(strs[i], &m->ambient->color) \
			&& free_str(str))
			parse_error(m, "Ambient: Invalid ambient color", strs, 1);
	}
	free_arr(strs);
	scalar(&m->ambient->color, m->ambient->ratio);
	return (0);
}

int	parse_light(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;

	str = ft_split_and_check(m, string, ' ', true);
	i = 1;
	if (arr_len(str) != 4 && free_str(string))
		parse_error(m, "Light: Invalid number of arguments", str, 1);
	m->lights[*j] = calloc_and_check(sizeof(t_light), 1, m, "Error\nLights");
	m->light_count++;
	while (str && str[i])
	{
		if (i == 1 && !dovector(m, str[i], &m->lights[*j]->position, false) \
			&& free_str(string))
			parse_error(m, "Light: Invalid coordinates", str, 1);
		if (i == 2 && check_double(str[i], &m->lights[*j]->brightness, true) \
			&& free_str(string))
			parse_error(m, "Light: Invalid brightness ratio", str, 1);
		if (i == 3 && !dovectorcolor(str[i], &m->lights[*j]->intensity) \
			&& free_str(string))
			parse_error(m, "Light: Invalid color", str, 1);
		i++;
	}
	free_arr(str);
	*j += 1;
	return (0);
}
