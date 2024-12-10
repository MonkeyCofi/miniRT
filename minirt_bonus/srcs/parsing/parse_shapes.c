/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 12:45:40 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 11:44:18 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_bonus_specs(t_minirt *m, t_mater *material, \
	char **tokens, t_bool is_sphere)
{
	int		i;
	int		clones[6];

	i = -1;
	ft_bzero(&clones, sizeof(int) * 6);
	while (tokens[++i])
	{
		if (!ft_strncmp(tokens[i], "pattern", 7))
			recognizepattern(m, tokens[i], material, clones);
		else if (!ft_strncmp(tokens[i], "specular", 8))
			recognizespecular(m, tokens[i], material, clones);
		else if (!ft_strncmp(tokens[i], "diffuse", 7))
			recognizediffuse(m, tokens[i], material, clones);
		else if (!ft_strncmp(tokens[i], "ambient", 7))
			recognizeambient(m, tokens[i], material, clones);
		else if (!ft_strncmp(tokens[i], "texture", 7))
		{
			set_sphere_only(clones, is_sphere);
			recognizetexture(m, tokens[i], material, clones);
		}
		else
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
		parse_error(m, "Invalid number of arguments", str, 1);
	m->shapes[*j] = alloc_shape(m);
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &m->shapes[*j]->coords, false) == false)
			parse_error(m, "Sphere: Invalid coordinates", str, 1);
		if (i == 2 && check_radius(m->shapes[*j], str[i], NULL))
			parse_error(m, "Sphere: Invalid diameter", str, 1);
		if (i == 3 && dovectorcolor(str[i], \
			&m->shapes[*j]->material->color) == false)
			parse_error(m, "Sphere: Invalid color", str, 1);
		if (i == 4 && parse_bonus_specs(m, \
			m->shapes[*j]->material, &str[i], true) && free_arr(str))
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
	char	**spl;

	spl = ft_split_and_check(m, str, ' ', true);
	i = 1;
	if (arr_len(spl) < 4 || arr_len(spl) > 8)
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
		if (i == 4 && parse_bonus_specs(m, m->shapes[*j]->material, &spl[i], 0) \
			&& free_arr(spl))
			return (write_and_return(m, "Error\nInvalid plane parameters\n", 1));
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
	if (arr_len(spl) < 6 || arr_len(spl) > 10)
		parse_error(m, "Cyl: Incorrect number of arguments", spl, 1);
	m->shapes[*j] = alloc_shape(m);
	while (spl && spl[i++])
	{
		if (i == 1 && !dovector(spl[i], &m->shapes[*j]->coords, false))
			parse_error(m, "Cyl: Invalid coordinates", spl, 1);
		if (i == 2 && !dovector(spl[i], &m->shapes[*j]->orientation, true))
			parse_error(m, "Cyl: Invalid orientation", spl, 1);
		if (i == 3 && check_radius(m->shapes[*j], spl[i], &m->shapes[*j]->r))
			parse_error(m, "Cyl: Invalid diameter", spl, 1);
		if (i == 4 && check_height(m->shapes[*j], spl[i], &m->shapes[*j]->h))
			parse_error(m, "Cyl: Invalid height", spl, 1);
		if (i == 5 && !dovectorcolor(spl[i], &m->shapes[*j]->material->color))
			parse_error(m, "Cyl: Invalid color", spl, 1);
		if (i == 6 && parse_bonus_specs(m, m->shapes[*j]->material, &spl[i], 0)
			&& free_arr(spl))
			return (1);
	}
	free_arr(spl);
	return (0);
}

int	parse_cone(t_minirt *m, char *str, int *j)
{
	int		i;
	char	**strs;
	double	height;

	strs = ft_split_and_check(m, str, ' ', true);
	i = 0;
	height = 0;
	if (arr_len(strs) < 5 || arr_len(strs) > 9)
		parse_error(m, "Cone: Invalid number of arguments", strs, 1);
	m->shapes[*j] = alloc_shape(m);
	while (strs && strs[i++])
	{
		if (i == 1 && !dovector(strs[i], &m->shapes[*j]->coords, false))
			parse_error(m, "Cone: Invalid cone coordinates", strs, 1);
		if (i == 2 && !dovector(strs[i], &m->shapes[*j]->orientation, true))
			parse_error(m, "Cone: Invalid cone orientation", strs, 1);
		if (i == 3 && check_radius(m->shapes[*j], strs[i], &height))
			parse_error(m, "Cone: Invalid cone height", strs, 1);
		if (i == 4 && !dovectorcolor(strs[i], &m->shapes[*j]->material->color))
			parse_error(m, "Cone: Invalid cone color", strs, 1);
		if (i == 5 && parse_bonus_specs(m, m->shapes[*j]->material, &strs[i], 0) \
			&& free_arr(strs))
			return (1);
	}
	free_arr(strs);
	m->shapes[*j]->h = height;
	return (0);
}
