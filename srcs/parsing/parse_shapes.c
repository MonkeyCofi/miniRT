/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:45:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 15:36:29 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*alloc_shape(t_minirt *m)
{
	t_shape	*shape;

	shape = calloc_and_check(sizeof(t_shape), 1, m, SHP_ERR);
	shape->material = create_default_material();
	if (!shape->material)
		return (NULL);
	return (shape);
}

int	parse_bonus_specs(t_mater *material, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (i == 0 && tokens[i] && recognizepattern(tokens[i], material))
			return (1);
		if (i == 1 && tokens[i] && recognizespecular(tokens[i], material))
			return (1);
		if (i == 2 && tokens[i] && recognizediffuse(tokens[i], material))
			return (1);
		if (i == 3 && tokens[i] && recognizeambient(tokens[i], material))
			return (1);
		i++;
	}
	return (0);
}

int	parse_sphere(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;
	double	diameter;

	str = ft_split(string, ' ');
	i = 1;
	if (arr_len(str) < 4 || arr_len(str) > 8)
		return (printf("Error\nIssue Lies in Sphere Arguments\n"), 1);
	m->shapes[*j] = alloc_shape(m);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &m->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Sphere Coordinates\n"), 1);
		if (i == 2 && check_radius(str[i], &diameter))
			return (printf("Error\nIssue Lies in Sphere Diameter\n"), 1);
		if (i == 3 && dovectorcolor(str[i], &m->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Sphere Color\n"), 1);
		if (i == 4 && parse_bonus_specs(m->shapes[*j]->material, &str[i]) == 1)
			return (1);
		i++;
	}
	free_arr(str);
	m->shapes[*j]->type = SPHERE;
	m->shapes[*j]->r = diameter / 2;
	return (0);
}

int	parse_plane(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;

	str = ft_split(string, ' ');
	i = 1;
	if (arr_len(str) < 4 || arr_len(str) > 8)
		return (printf("Error\nIssue Lies in Plane Arguments\n"), 1);
	m->shapes[*j] = alloc_shape(m);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &m->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Plane Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], &m->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Plane Orientation\n"), 1);
		if (i == 3 && dovectorcolor(str[i], &m->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Plane Color\n"), 1);
		if (i == 4 && parse_bonus_specs(m->shapes[*j]->material, &str[i]) == 1)
			return (1);
		i++;
	}
	free_arr(str);
	m->shapes[*j]->type = PLANE;
	m->object_count += 1;
	*j += 1;
	return (0);
}

int	parse_cylinder(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;

	str = ft_split(string, ' ');
	i = 0;
	if (arr_len(str) < 6 || arr_len(str) > 10)
		return (printf("Error\nIssue Lies in Cylinder Arguments\n"), 1);
	m->shapes[*j] = alloc_shape(m);
	while (str && str[i++])
	{
		if (i == 1 && dovector(str[i], &m->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Cylinder Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], &m->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Cylinder Orientation\n"), 1);
		if (i == 3 && check_radius(str[i], &m->shapes[*j]->r))
			return (printf("Error\nIssue Lies in Cylinder Diameter\n"), 1);
		if (i == 4 && check_radius(str[i], &m->shapes[*j]->h))
			return (printf("Error\nIssue Lies in Cylinder Height\n"), 1);
		if (i == 5 && dovectorcolor(str[i], &m->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Cylinder Color\n"), 1);
		if (i == 6 && parse_bonus_specs(m->shapes[*j]->material, &str[i]) == 1)
			return (1);
	}
	free_arr(str);
	return (0);
}
