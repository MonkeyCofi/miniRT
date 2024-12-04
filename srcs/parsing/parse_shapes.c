/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:45:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 10:43:39 by ahaarij          ###   ########.fr       */
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

int	parse_bonus_specs(t_minirt *m, t_mater *material, char **tokens)
{
	int		i;
	int		clones[5];

	i = -1;
	ft_bzero(&clones, sizeof(int) * 5);
	while (tokens[++i])
	{
		if (tokens[i] && ft_strncmp(tokens[i], "pattern", 7) == 0 && \
			recognizepattern(m, tokens[i], material, clones))
			return (1);
		if (tokens[i] && ft_strncmp(tokens[i], "specular", 8) == 0 && \
			recognizespecular(m, tokens[i], material, clones))
			return (1);
		if (tokens[i] && ft_strncmp(tokens[i], "diffuse", 7) == 0 && \
			recognizediffuse(m, tokens[i], material, clones))
			return (1);
		if (tokens[i] && ft_strncmp(tokens[i], "ambient", 7) == 0 && \
			recognizeambient(m, tokens[i], material, clones))
			return (1);
		if (tokens[i] && ft_strncmp(tokens[i], "texture", 7) == 0 && \
			recognizetexture(m, tokens[i], material, clones))
			return (1);
	}
	return (0);
}

int	parse_sphere(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;

	str = ft_split_and_check(m, string, ' ', true);
	i = 1;
	if (arr_len(str) < 4 || arr_len(str) > 9)
		parse_error(m, "Error: Invalid number of arguments", string, str);
	m->shapes[*j] = alloc_shape(m);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &m->shapes[*j]->coords, false) == false)
			parse_error(m, "Error: Sphere: Invalid coordinates", string, str);
		if (i == 2 && check_radius(m->shapes[*j], str[i], NULL))
			parse_error(m, "Error: Sphere: Invalid diameter", string, str);
		if (i == 3 && dovectorcolor(str[i], \
			&m->shapes[*j]->material->color) == false)
			parse_error(m, "Error: Sphere: Invalid color", string, str);
		if (i == 4 && parse_bonus_specs(m, \
			m->shapes[*j]->material, &str[i]) == 1)
			return (1);
		i++;
	}
	free_arr(str);
	m->shapes[*j]->type = SPHERE;
	return (0);
}

int	parse_plane(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**strs;

	strs = ft_split_and_check(m, str, ' ', true);
	i = 1;
	if (arr_len(strs) < 4 || arr_len(strs) > 8)
		parse_error(m, "Error: Plane: Invalid number of arguments", str, strs);
	m->shapes[*j] = alloc_shape(m);
	while (strs && strs[i])
	{
		if (i == 1 && !dovector(strs[i], &m->shapes[*j]->coords, false))
			parse_error(m, "Error: Plane: Invalid coordinates", str, strs);
		if (i == 2 && !dovector(strs[i], &m->shapes[*j]->orientation, true))
			parse_error(m, "Error: Plane: Invalid orientation", str, strs);
		if (i == 3 && !dovectorcolor(strs[i], &m->shapes[*j]->material->color))
			parse_error(m, "Error: Plane: Invalid color", str, strs);
		if (i == 4 && parse_bonus_specs(m, m->shapes[*j]->material, &strs[i]))
			return (1);
		i++;
	}
	free_arr(strs);
	m->shapes[*j]->type = PLANE;
	m->object_count += 1;
	*j += 1;
	return (0);
}

int	parse_cylinder(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**strs;

	strs = ft_split_and_check(m, str, ' ', true);
	i = 0;
	if (arr_len(strs) < 6 || arr_len(strs) > 10)
		parse_error(m, "Error: Cyl: Incorrect number of arguments", str, strs);
	m->shapes[*j] = alloc_shape(m);
	while (strs && strs[i++])
	{
		if (i == 1 && !dovector(strs[i], &m->shapes[*j]->coords, false))
			parse_error(m, "Error: Cyl: Invalid coordinates", str, strs);
		if (i == 2 && !dovector(strs[i], &m->shapes[*j]->orientation, true))
			parse_error(m, "Error: Cyl: Invalid orientation", str, strs);
		if (i == 3 && printf("radius: %s\n", strs[i]) && check_radius(m->shapes[*j], strs[i], &m->shapes[*j]->r))
			parse_error(m, "Error: Cyl: Invalid diameter", str, strs);
		if (i == 4 && printf("radius: %s\n", strs[i]) && check_height(m->shapes[*j], strs[i], &m->shapes[*j]->h))
			parse_error(m, "Error: Cyl: Invalid height", str, strs);
		if (i == 5 && !dovectorcolor(strs[i], &m->shapes[*j]->material->color))
			parse_error(m, "Error: Cyl: Invalid color", str, strs);
		if (i == 6 && parse_bonus_specs(m, m->shapes[*j]->material, &strs[i]))
			return (1);
	}
	// printf("%f\n", m->shapes[*j]->r);
	free_arr(strs);
	return (0);
}
