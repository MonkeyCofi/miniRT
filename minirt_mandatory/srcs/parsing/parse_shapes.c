/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:45:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/05 20:26:37 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;

	str = ft_split_and_check(m, string, ' ', true);
	i = 1;
	if (arr_len(str) != 4)
		parse_error(m, "Sphere: Invalid number of arguments", str, 1);
	m->shapes[*j] = alloc_shape(m);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &m->shapes[*j]->coords, false) == 0)
			parse_error(m, "Sphere: Invalid coordinates", str, 1);
		if (i == 2 && check_radius(m->shapes[*j], str[i], NULL))
			parse_error(m, "Sphere: Invalid diameter", str, 1);
		if (i == 3 && dovectorcolor(str[i], \
			&m->shapes[*j]->material->color) == false)
			parse_error(m, "Sphere: Invalid color", str, 1);
		i++;
	}
	free_arr(str);
	m->shapes[*j]->type = SPHERE;
	return (0);
}

int	parse_plane(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**spl;

	spl = ft_split_and_check(m, str, ' ', true);
	i = 1;
	if (arr_len(spl) != 4)
		parse_error(m, "Plane: Invalid number of arguments", spl, 1);
	m->shapes[*j] = alloc_shape(m);
	while (spl && spl[i])
	{
		if (i == 1 && !dovector(spl[i], &m->shapes[*j]->coords, false))
			parse_error(m, "Plane: Invalid coordinates", spl, 1);
		if (i == 2 && !dovector(spl[i], &m->shapes[*j]->orientation, true))
			parse_error(m, "Plane: Invalid orientation", spl, 1);
		if (i == 3 && !dovectorcolor(spl[i], &m->shapes[*j]->material->color))
			parse_error(m, "Plane: Invalid color", spl, 1);
		i++;
	}
	free_arr(spl);
	m->shapes[*j]->type = PLANE;
	m->object_count += 1;
	*j += 1;
	return (0);
}

int	parse_cylinder(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**spl;

	spl = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if (arr_len(spl) != 6)
		parse_error(m, "Cylinder: Incorrect number of arguments", spl, 1);
	m->shapes[*j] = alloc_shape(m);
	while (spl && spl[i++])
	{
		if (i == 1 && !dovector(spl[i], &m->shapes[*j]->coords, false))
			parse_error(m, "Cylinder: Invalid coordinates", spl, 1);
		if (i == 2 && !dovector(spl[i], &m->shapes[*j]->orientation, true))
			parse_error(m, "Cylinder: Invalid orientation", spl, 1);
		if (i == 3 && check_radius(m->shapes[*j], spl[i], &m->shapes[*j]->r))
			parse_error(m, "Cylinder: Invalid diameter", spl, 1);
		if (i == 4 && check_height(m->shapes[*j], spl[i], &m->shapes[*j]->h))
			parse_error(m, "Cylinder: Invalid height", spl, 1);
		if (i == 5 && !dovectorcolor(spl[i], &m->shapes[*j]->material->color))
			parse_error(m, "Cylinder: Invalid color", spl, 1);
	}
	free_arr(spl);
	return (0);
}
