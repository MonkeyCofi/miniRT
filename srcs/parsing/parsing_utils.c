/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:48:18 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/02 18:11:12 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	is_in_bounds(t_tuple *vector)
{
	if (vector->x > 1 || vector->x < -1)
		return (false);
	if (vector->y > 1 || vector->y < -1)
		return (false);
	if (vector->z > 1 || vector->z < -1)
		return (false);
	return (true);
}

t_bool	dovector(char *string, t_tuple *calc, t_bool should_norm)
{
	char	**str;
	int		i;

	i = -1;
	str = ft_split(string, ',');
	while (str && str[++i])
	{
		if (!is_double(str[i]) && free_arr(str))
			return (false);
	}
	if (arr_len(str) != 3 && free_arr(str))
		return (false);
	else
	{
		calc->x = str_to_double(str[0]);
		calc->y = str_to_double(str[1]);
		calc->z = str_to_double(str[2]);
	}
	if (should_norm == true && free_arr(str))
	{
		normalize(calc);
		return (is_in_bounds(calc));
	}
	return (true);
}

t_bool	dovectorcolor(char *string, t_tuple *calc)
{
	char	**str;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	str = ft_split(string, ',');
	while (str && str[++i])
		if (!is_double(str[i]))
			ret = 1;
	if (arr_len(str) != 3)
		ret = 1;
	else if (ret != 1)
	{
		calc->x = str_to_double(str[0]) / 255.0;
		calc->y = str_to_double(str[1]) / 255.0;
		calc->z = str_to_double(str[2]) / 255.0;
	}
	free_arr(str);
	return (is_in_bounds(calc));
}

static t_bool	get_filename_and_open_texture(t_minirt *m, t_mater *material, char *name)
{
	char	*filename;
	
	filename = ft_strtrim(name, "\"");
	if (!filename)
	{
		write_err("Error: Str_trim: Failed to trim string", '\n');
		free_minirt(m);
	}
	material->texture = calloc_and_check(sizeof(t_img), 1, m, IMG_ERR);
	if (open_image(m, material, filename) == error)
	{
		free(filename);
		return (false);
	}
	return (true);
}

t_bool	open_texture(t_minirt *m, t_mater *material, char **params)
{
	int	i;

	i = -1;
	while (params[++i])
	{
		if (i == 0 && ft_strncmp(params[i], "texture", ft_strlen("texture")) != 0)
		{
			write_two_errs(m, "Error: Texture: Invalid keyword", 0, params[i], '\n');
			free_arr(params);
			free_minirt(m);
		}
		if (i == 1)
		{
			if (ft_strncmp(params[i], "none", ft_strlen(params[i])) == 0)
			{
				free_arr(params);
				return (false);
			}
			get_filename_and_open_texture(m, material, params[i]);
		}
	}
	return (true);
}
