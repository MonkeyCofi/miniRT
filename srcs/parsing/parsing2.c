/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:22:45 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 15:29:31 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
			return (printf("Error\nIssue Lies in Specular Keyword\n"), 1);
		if (i == 1 && check_double(str[i], &material->specular))
			return (printf("Error\nIssue Lies in Specular Value\n"), 1);
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
