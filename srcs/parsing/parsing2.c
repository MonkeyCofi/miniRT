/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:22:45 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/28 19:38:23 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	recognizetexture(t_minirt *m, char *string, t_mater *material)
{
	char	**params;
	t_img	*img;
	char	*filename;
	int		i;

	params = ft_split(string, '=');
	if (!params)
	{
		write_err("Error: Unable to allocate memory for params", 'y');
		free_minirt(m);
	}
	i = -1;
	while (params[++i])
	{
		if (i == 0 && ft_strncmp(params[i], "texture", ft_strlen("texture")) != 0)
		{
			write_err("Error: Invalid keyword: ", 0);
			write_err(params[i], 'y');
			free_arr(params);
			free_minirt(m);
		}
		if (i == 1)
		{
			filename = ft_strtrim(params[i], "\"");
			material->texture = calloc_and_check(sizeof(t_img), 1, m, IMG_ERR);
			img = material->texture;
			img->img = mlx_xpm_file_to_image(m->mlx->mlx, filename, &img->img_width, &img->img_height);
			if (!img->img)
			{
				write_err(IMG_ERR, 0);
				write_err("Error string: ", 0);
				write_err(string, 'y');
				free_arr(params);
				free(filename);
				free_minirt(m);
			}
			img->img_addr = mlx_get_data_addr(img->img, &img->bpp, \
				&img->line_length, &img->endian);
			if (!img->img_addr)
			{
				write_err("Error: Could not fetch texture data", 'y');
				write_err("Error string: ", 0);
				write_err(string, 'y');
				free_arr(params);
				free(filename);
				free_minirt(m);
			}
		}
	}
	free_arr(params);
	free(filename);
	return (0);
}

int	recognizespecular(char *string, t_mater *material)
{
	int		i;
	char	**str;

	i = -1;
	if (ft_strncmp(string, "specular=default", 16) == 0)
		return (0);
	str = ft_split(string, '=');
	if (arr_len(str) != 2)
		return (1);
	while (str && str[++i])
	{
		if (i == 0 && ft_strncmp(str[i], "specular", 8) != 0)
		{
			free_arr(str);
			return (printf("Error\nIssue Lies in Specular Keyword\n"), 1);
		}
		if (i == 1 && check_double(str[i], &material->specular))
		{
			free_arr(str);
			return (printf("Error\nIssue Lies in Specular Value\n"), 1);
		}
	}
	free_arr(str);
	return (0);
}

int	recognizediffuse(char *string, t_mater *material)
{
	int		i;
	char	**str;

	i = -1;
	if (ft_strncmp(string, "diffuse=default", 15) == 0)
		return (0);
	str = ft_split(string, '=');
	if (arr_len(str) != 2)
		return (1);
	while (str && str[++i])
	{
		if (i == 0 && ft_strncmp(str[i], "diffuse", 7) != 0)
			return (printf("Error\nIssue Lies in Diffuse Keyword\n"), 1);
		if (i == 1 && check_double(str[i], &material->diffuse))
			return (printf("Error\nIssue Lies in Diffuse Value\n"), 1);
	}
	free_arr(str);
	return (0);
}

int	recognizeambient(char *string, t_mater *material)
{
	int		i;
	char	**str;

	i = -1;
	if (ft_strncmp(string, "ambient=default", 15) == 0)
		return (0);
	str = ft_split(string, '=');
	if (arr_len(str) != 2)
		return (1);
	while (str && str[++i])
	{
		if (i == 0 && ft_strncmp(str[i], "ambient", 8) != 0)
			return (printf("Error\nIssue Lies in Ambient Keyword\n"), 1);
		if (i == 1 && check_double(str[i], &material->ambient))
			return (printf("Error\nIssue Lies in Ambient Value\n"), 1);
	}
	free_arr(str);
	return (0);
}

int	recognizepattern(char *string, t_mater *material)
{
	int		i;
	char	**str;

	i = -1;
	if (ft_strncmp(string, "pattern=no", 10) == 0)
		return (0);
	str = ft_split(string, '=');
	if (arr_len(str) != 2)
		return (1);
	while (str && str[++i])
	{
		if (i == 0 && ft_strncmp(str[i], "pattern", 7) != 0)
			return (printf("Error\nIssue Lies in Pattern Keyword\n"), 1);
		if (i == 1 && dovectorcolor(str[i], &material->pattern.color_two))
			return (printf("Error\nIssue Lies in Pattern Color\n"), 1);
	}
	free_arr(str);
	material->is_patterned = true;
	material->pattern.color_one = material->color;
	return (0);
}

int	parse_camera(t_minirt *minirt, char *string)
{
	char	**str;
	int		i;

	i = 0;
	if (minirt->cam->flag != 0)
		return (printf("Error\nIssue Lies in Number of Cameras \
					(Should Be 1)!\n"), 1);
	else
		minirt->cam->flag = 1;
	str = ft_split(string, ' ');
	if (arr_len(str) != 4)
		return (printf("Error\nIssue Lies in Camera Arguments\n"), 1);
	while (str[i] && str[i++])
	{
		if (i == 1 && dovector(str[i], &minirt->from))
			return (printf("Error\nIssue Lies in Camera Coordinates\n"), 1);
		if (i == 2 && dovectororientationf(str[i], &minirt->to))
			return (printf("Error\nIssue Lies in Camera Orientation\n"), 1);
		if (i == 3 && check_ulong(str[i], &minirt->cam->fov))
			return (printf("Error\nIssue Lies in Camera FOV\n"), 1);
		minirt->from.w = POINT;
	}
	free_arr(str);
	return (0);
}
