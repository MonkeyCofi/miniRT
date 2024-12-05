/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:22:45 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 22:06:37 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	recognizetexture(t_minirt *m, char *string, t_mater *material, int *clones)
{
	char	**params;

	if (clones[5])
		parse_error(m, "Error: Texture: Only spheres can have textures", \
			NULL, NULL);
	if (clones[4])
		parse_error(m, "Error: Texture: Texture already exists", string, NULL);
	params = ft_split(string, '=');
	if (!params)
	{
		write_err("Error: Unable to allocate memory for params", '\n');
		free_minirt(m);
	}
	if (open_texture(m, material, params) == false)
		free_arr(params);
	clones[4] = 1;
	free_arr(params);
	return (0);
}

int	recognizespecular(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[1])
		parse_error(m, "Error: Specular: Specular already exists", str, NULL);
	if (ft_strncmp(str, "specular=default", 16) == 0)
	{
		clones[1] = 1;
		return (0);
	}
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2)
		return (1);
	while (strs && strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "specular", 8) != 0)
			parse_error(m, "Error: Specular: Invalid keyword", str, strs);
		if (i == 1 && check_double(strs[i], &material->specular, false))
			parse_error(m, "Error: Specular: Invalid value", str, strs);
	}
	free_arr(strs);
	clones[1] = 1;
	return (0);
}

int	recognizediffuse(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[2])
		parse_error(m, "Error: Diffuse: Diffuse already exists", str, NULL);
	if (ft_strncmp(str, "diffuse=default", 15) == 0)
	{
		clones[2] = 1;
		return (0);
	}
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2)
		return (1);
	while (strs && strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "diffuse", 7) != 0)
			parse_error(m, "Error: Diffuse: Invalid keyword", str, strs);
		if (i == 1 && check_double(strs[i], &material->diffuse, false))
			parse_error(m, "Error: Diffuse: Invalid value", str, strs);
	}
	free_arr(strs);
	clones[2] = 1;
	return (0);
}

int	recognizeambient(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[3])
		parse_error(m, "Error: Shape ambient: Shape ambient already exists", \
			str, NULL);
	if (ft_strncmp(str, "ambient=default", 15) == 0)
	{
		clones[3] = 1;
		return (0);
	}
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2)
		return (1);
	while (strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "ambient", 7) != 0)
			parse_error(m, "Error: Shape ambient: Invalid keyword", str, strs);
		if (i == 1 && check_double(strs[i], &material->ambient, false))
			parse_error(m, "Error: Shape ambient: Invalid value", str, strs);
	}
	free_arr(strs);
	clones[3] = 1;
	return (0);
}

int	recognizepattern(t_minirt *m, char *str, t_mater *material, int *clones)
{
	int		i;
	char	**strs;

	i = -1;
	if (clones[0])
		parse_error(m, "Error: Pattern: Pattern already exists", str, NULL);
	if (ft_strncmp(str, "pattern=no", 10) == 0)
		return (0);
	strs = ft_split_and_check(m, str, '=', true);
	if (arr_len(strs) != 2)
		return (1);
	while (strs && strs[++i])
	{
		if (i == 0 && ft_strncmp(strs[i], "pattern", 7) != 0)
			parse_error(m, "Error: Pattern: Invalid keyword", str, strs);
		if (i == 1 && dovectorcolor(strs[i], &material->pattern.color_two) \
		== false)
			parse_error(m, "Error: Pattern: Invalid color", str, strs);
	}
	free_arr(strs);
	material->is_patterned = true;
	material->pattern.color_one = material->color;
	clones[0] = 1;
	return (0);
}
