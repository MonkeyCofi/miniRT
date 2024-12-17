/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:45:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 20:05:33 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**strs;

	strs = ft_split_and_check(m, str, ' ', true);
	i = 1;
	if (arr_len(strs) != 4 && free_str(str))
		parse_error(m, "Sphere: Invalid number of arguments", strs, 1);
	m->shapes[*j] = alloc_shape(m);
	while (strs && strs[i])
	{
		if (i == 1 && !dovector(m, strs[i], &m->shapes[*j]->coords, false) \
			&& free_str(str))
			parse_error(m, "Sphere: Invalid coordinates", strs, 1);
		if (i == 2 && check_radius(m->shapes[*j], strs[i], NULL) \
			&& free_str(str))
			parse_error(m, "Sphere: Invalid diameter", strs, 1);
		if (i == 3 && !dovectorcolor(strs[i], \
			&m->shapes[*j]->material->color) && free_str(str))
			parse_error(m, "Sphere: Invalid color", strs, 1);
		i++;
	}
	free_arr(strs);
	m->shapes[*j]->type = SPHERE;
	return (0);
}

int	parse_plane(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**spl;

	spl = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if (arr_len(spl) != 4 && free_str(str))
		parse_error(m, "Plane: Invalid number of arguments", spl, 1);
	m->shapes[*j] = alloc_shape(m);
	while (spl && spl[i++])
	{
		if (i == 1 && !dovector(m, spl[i], &m->shapes[*j]->coords, false) \
			&& free_str(str))
			parse_error(m, "Plane: Invalid coordinates", spl, 1);
		if (i == 2 && !dovector(m, spl[i], &m->shapes[*j]->orientation, true) \
			&& free_str(str))
			parse_error(m, "Plane: Invalid orientation", spl, 1);
		if (i == 3 && !dovectorcolor(spl[i], &m->shapes[*j]->material->color) \
			&& free_str(str))
			parse_error(m, "Plane: Invalid color", spl, 1);
	}
	free_arr(spl);
	m->shapes[*j]->type = PLANE;
	*j += 1;
	return (0);
}

void	parse_cylinder_helper(t_minirt *m, char **spl, char *str, int *j)
{
	int	i;

	i = 3;
	while (spl[i++])
	{
		if (i == 4 && check_height(m->shapes[*j], spl[i], &m->shapes[*j]->h) \
			&& free_str(str))
			parse_error(m, "Cylinder: Invalid height", spl, 1);
		if (i == 5 && !dovectorcolor(spl[i], &m->shapes[*j]->material->color) \
			&& free_str(str))
			parse_error(m, "Cylinder: Invalid color", spl, 1);
	}
}

int	parse_cylinder(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**spl;

	spl = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if (arr_len(spl) != 6 && free_str(str))
		parse_error(m, "Cylinder: Incorrect number of arguments", spl, 1);
	m->shapes[*j] = alloc_shape(m);
	while (spl && spl[i++])
	{
		if (i == 1 && !dovector(m, spl[i], &m->shapes[*j]->coords, false) \
			&& free_str(str))
			parse_error(m, "Cylinder: Invalid coordinates", spl, 1);
		if (i == 2 && !dovector(m, spl[i], &m->shapes[*j]->orientation, true) \
			&& free_str(str))
			parse_error(m, "Cylinder: Invalid orientation", spl, 1);
		if (i == 3 && check_radius(m->shapes[*j], spl[i], &m->shapes[*j]->r) \
			&& free_str(str))
			parse_error(m, "Cylinder: Invalid diameter", spl, 1);
		parse_cylinder_helper(m, spl, str, j);
	}
	return (free_arr(spl), 0);
}
