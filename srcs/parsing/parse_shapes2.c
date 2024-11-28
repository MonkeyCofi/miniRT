/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_shapes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 09:55:28 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/28 17:47:15 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ambient(t_minirt *minirt, char *string)
{
	int		i;
	char	**str;

	if (minirt->ambient->flag != 0)
		return (printf("Error\nIssue Lies in Number of \
					Ambient (Should Be 1)!\n"), 1);
	else
		minirt->ambient->flag = 1;
	str = ft_split(string, ' ');
	i = 1;
	if (arr_len(str) != 3)
		return (printf("Error\nIssue Lies in Ambient Arguments!\n"), 1);
	while (string && string[i])
	{
		if (i == 1 && check_double(str[i], &minirt->ambient->ratio))
			return (printf("Error\nIssue Lies in Ambient Ratio\n"), 1);
		if (i == 2 && dovectorcolor(str[i], &minirt->ambient->color))
			return (printf("Error\nIssue Lies in Ambient Color\n"), 1);
		i++;
	}
	free_arr(str);
	scalar(&minirt->ambient->color, minirt->ambient->ratio);
	return (0);
}

int	parse_cone(t_minirt *m, char *string, int *j)
{
	int		i;
	char	**str;
	double	height;

	str = ft_split(string, ' ');
	i = 0;
	if (arr_len(str) < 5 || arr_len(str) > 9)
		return (printf("Error\nIssue Lies in Cone Arguments!\n"), 1);
	m->shapes[*j] = alloc_shape(m);
	while (str && str[i++])
	{
		if (i == 1 && dovector(str[i], &m->shapes[*j]->coords))
			return (printf("Error\nIssue Lies in Cone Coordinates\n"), 1);
		if (i == 2 && dovectororientation(str[i], &m->shapes[*j]->orientation))
			return (printf("Error\nIssue Lies in Cone Orientation\n"), 1);
		if (i == 3 && check_radius(str[i], &height))
			return (printf("Error\nIssue Lies in Cone Height\n"), 1);
		if (i == 4 && dovectorcolor(str[i], &m->shapes[*j]->material->color))
			return (printf("Error\nIssue Lies in Cone Color\n"), 1);
		if (i == 5 && parse_bonus_specs(m, m->shapes[*j]->material, &str[i]) == 1)
			return (1);
	}
	free_arr(str);
	m->shapes[*j]->h = height;
	return (0);
}

int	check_doubleb(char *str, double *num)
{
	if (!is_double(str))
		return (1);
	*num = str_to_double(str);
	if (*num > 1 || *num < 0)
		return (1);
	return (0);
}

int	parse_light(t_minirt *minirt, char *string, int *j)
{
	int		i;
	char	**str;

	str = ft_split(string, ' ');
	i = 1;
	if (arr_len(str) != 4)
		return (printf("Error\nIssue Lies in Light Arguments!\n"), 1);
	minirt->lights[*j] = ft_calloc(1, sizeof(t_light));
	while (str && str[i])
	{
		if (i == 1 && dovector(str[i], &minirt->lights[*j]->position))
			return (printf("Error\nIssue Lies in Light Coords"), 1);
		if (i == 2 && check_doubleb(str[i], &minirt->lights[*j]->brightness))
			return (printf("Error\nIssue Lies in Light Brightness"), 1);
		if (i == 3 && dovectorcolor(str[i], &minirt->lights[*j]->intensity))
			return (printf("Error\nIssue Lies in Light Color"), 1);
		i++;
	}
	free_arr(str);
	minirt->light_count++;
	*j += 1;
	return (0);
}
