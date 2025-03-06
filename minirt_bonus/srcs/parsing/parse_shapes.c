/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:45:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 20:57:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_sphere(t_minirt *m, char *s, int *j)
{
	int		i;
	char	**st;

	st = ft_split_and_check(m, s, ' ', true);
	i = 0;
	if ((arr_len(st) < 4 || arr_len(st) > 9) && free_str(s))
		parse_error(m, "Invalid number of arguments", st, 1);
	m->shapes[*j] = alloc_shape(m);
	while (st && st[i++])
	{
		if (i == 1 && !dovector(m, st[i], &m->shapes[*j]->coords, false) \
			&& free_str(s))
			parse_error(m, "Sphere: Invalid coordinates", st, 1);
		if (i == 2 && check_radius(m->shapes[*j], st[i], NULL) && free_str(s))
			parse_error(m, "Sphere: Invalid diameter", st, 1);
		if (i == 3 && dovectorcolor(st[i], \
			&m->shapes[*j]->material->color) == false && free_str(s))
			parse_error(m, "Sphere: Invalid color", st, 1);
		if (i == 4 && parse_bon_sp(m, m->shapes[*j], &st[i], true) \
			&& free_arr(st))
			return (1);
	}
	free_arr(st);
	m->shapes[*j]->type = SPHERE;
	return (0);
}

int	parse_plane(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**s;

	s = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if ((arr_len(s) < 4 || arr_len(s) > 8) && free_str(str))
		parse_error(m, "Plane: Invalid number of arguments", s, 1);
	m->shapes[*j] = alloc_shape(m);
	while (s && s[i++])
	{
		if (i == 1 && !dovector(m, s[i], &m->shapes[*j]->coords, false) \
			&& free_str(str))
			parse_error(m, "Plane: Invalid coordinates", s, 1);
		if (i == 2 && !dovector(m, s[i], &m->shapes[*j]->orientation, true) \
			&& free_str(str))
			parse_error(m, "Plane: Invalid orientation", s, 1);
		if (i == 3 && !dovectorcolor(s[i], &m->shapes[*j]->material->color) \
			&& free_str(str))
			parse_error(m, "Plane: Invalid color", s, 1);
		if (i == 4 && parse_bon_sp(m, m->shapes[*j], &s[i], 0) && free_arr(s))
			return (write_and_return(m, "Error\nInvalid plane params\n", 1));
	}
	free_arr(s);
	m->shapes[*j]->type = PLANE;
	return ((*j)++, 0);
}

static inline int	parse_cylinder_helper(t_minirt *m, \
	char **s, int *j, char *str)
{
	int	i;

	i = 3;
	while (s[i++])
	{
		if (i == 4 && check_height(m->shapes[*j], s[i], \
		&m->shapes[*j]->h) && free_str(str))
			parse_error(m, "Cyl: Invalid height", s, 1);
		if (i == 5 && !dovectorcolor(s[i], \
		&m->shapes[*j]->material->color) && free_str(str))
			parse_error(m, "Cyl: Invalid color", s, 1);
		if (i == 6 && parse_bon_sp(m, \
		m->shapes[*j], &s[i], 0) && free_arr(s))
			return (1);
	}
	return (0);
}

int	parse_cylinder(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**s;

	s = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if ((arr_len(s) < 6 || arr_len(s) > 10) && free_str(str))
		parse_error(m, "Cyl: Incorrect number of arguments", s, 1);
	m->shapes[*j] = alloc_shape(m);
	while (s && s[i++])
	{
		if (i == 1 && !dovector(m, s[i], \
		&m->shapes[*j]->coords, false) && free_str(str))
			parse_error(m, "Cyl: Invalid coordinates", s, 1);
		if (i == 2 && !dovector(m, s[i], \
		&m->shapes[*j]->orientation, true) && free_str(str))
			parse_error(m, "Cyl: Invalid orientation", s, 1);
		if (i == 3 && check_radius(m->shapes[*j], \
		s[i], &m->shapes[*j]->r) && free_str(str))
			parse_error(m, "Cyl: Invalid diameter", s, 1);
		if (parse_cylinder_helper(m, s, j, str) == 1)
			return (1);
	}
	free_arr(s);
	return (0);
}

int	parse_cone(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**strs;

	strs = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if (arr_len(strs) < 5 || arr_len(strs) > 9)
		parse_error(m, "Cone: Invalid number of arguments", strs, 1);
	m->shapes[*j] = alloc_shape(m);
	while (strs && strs[i++])
	{
		if (i == 1 && !dovector(m, strs[i], \
		&m->shapes[*j]->coords, false) && free_str(str))
			parse_error(m, "Cone: Invalid cone coordinates", strs, 1);
		if (i == 2 && !dovector(m, strs[i], \
		&m->shapes[*j]->orientation, true) && free_str(str))
			parse_error(m, "Cone: Invalid cone orientation", strs, 1);
		if (parse_cone_helper(m, strs, str, j) == 1)
			return (1);
	}
	free_arr(strs);
	return (0);
}
