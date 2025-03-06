/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:48:18 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 20:59:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_cone_helper(t_minirt *m, char **strs, char *str, int *j)
{
	int	i;

	i = 2;
	while (strs[i++])
	{
		if (i == 3 && check_radius(m->shapes[*j], strs[i], &m->shapes[*j]->h))
		{
			free_str(str);
			parse_error(m, "Cone: Invalid cone height", strs, 1);
		}
		if (i == 4 && !dovectorcolor(strs[i], &m->shapes[*j]->material->color))
		{
			free_str(str);
			parse_error(m, "Cone: Invalid cone color", strs, 1);
		}
		if (i == 5 && parse_bon_sp(m, m->shapes[*j], &strs[i], 0) \
		&& free_arr(strs))
			return (1);
	}
	return (0);
}

t_bool	is_in_bounds(t_tuple *vector, t_bool for_color)
{
	if (for_color == true)
	{
		if (vector->x > 1 || vector->x < 0)
			return (false);
		if (vector->y > 1 || vector->y < 0)
			return (false);
		if (vector->z > 1 || vector->z < 0)
			return (false);
		return (true);
	}
	if (vector->x > 1 || vector->x < -1)
		return (false);
	if (vector->y > 1 || vector->y < -1)
		return (false);
	if (vector->z > 1 || vector->z < -1)
		return (false);
	return (true);
}

t_bool	dovector(t_minirt *m, char *string, t_tuple *calc, t_bool should_norm)
{
	char	**str;
	int		i;

	i = -1;
	str = ft_split_and_check(m, string, ',', 1);
	while (str && str[++i])
	{
		if (!is_double(str[i]) && free_arr(str))
			return (false);
	}
	if (arr_len(str) != 3 && free_arr(str))
		return (false);
	calc->x = str_to_double(str[0]);
	calc->y = str_to_double(str[1]);
	calc->z = str_to_double(str[2]);
	if (should_norm && free_arr(str))
	{
		if (check_magnitude(m, calc, string) == 0)
			return (false);
		normalize(calc);
		return (is_in_bounds(calc, false));
	}
	free_arr(str);
	return (true);
}

t_bool	dovectorcolor(char *string, t_tuple *calc)
{
	char	**str;
	int		i;

	i = -1;
	str = ft_split(string, ',');
	while (str && str[++i])
		if (!is_double(str[i]) && free_arr(str))
			return (false);
	if (arr_len(str) != 3 && free_arr(str))
		return (false);
	calc->x = str_to_double(str[0]) / 255.0;
	calc->y = str_to_double(str[1]) / 255.0;
	calc->z = str_to_double(str[2]) / 255.0;
	free_arr(str);
	return (is_in_bounds(calc, true));
}

int	parse_bon_sp(t_minirt *m, t_shape *shape, \
	char **tokens, t_bool is_sphere)
{
	int		i;
	int		ret;
	int		clones[6];

	i = -1;
	ft_bzero(&clones, sizeof(int) * 6);
	ret = 0;
	while (tokens[++i] && ret != 1)
	{
		if (!ft_strncmp(tokens[i], "pattern", 7))
			ret = recognizepattern(m, tokens[i], shape->material, clones);
		else if (!ft_strncmp(tokens[i], "specular", 8))
			ret = recognizespecular(m, tokens[i], shape->material, clones);
		else if (!ft_strncmp(tokens[i], "diffuse", 7))
			ret = recognizediffuse(m, tokens[i], shape->material, clones);
		else if (!ft_strncmp(tokens[i], "ambient", 7))
			ret = recognizeambient(m, tokens[i], shape->material, clones);
		else if (!ft_strncmp(tokens[i], "texture", 7) && \
			set_sphere_only(clones, is_sphere))
			ret = recognizetexture(m, tokens[i], shape->material, clones);
		else
			return (1);
	}
	return (ret);
}
