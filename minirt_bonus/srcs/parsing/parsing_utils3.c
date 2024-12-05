/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:35:15 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/05 19:34:45 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*alloc_shape(t_minirt *m)
{
	t_shape	*shape;

	shape = calloc_and_check(sizeof(t_shape), 1, m, SHP_ERR);
	shape->material = create_default_material(m);
	if (!shape->material)
		return (NULL);
	return (shape);
}

int	check_radius(t_shape *shape, char *str, double *num)
{
	double	res;

	if (!is_double(str))
		return (1);
	if (!num)
	{
		res = str_to_double(str);
		if (res / 2 < 0 || res < 0)
			return (1);
		shape->r = res / 2;
		return (0);
	}
	*num = str_to_double(str);
	if (*num / 2 < 0 || *num < 0)
		return (1);
	shape->r = (*num) / 2;
	return (0);
}

int	set_sphere_only(int *clones, t_bool is_sphere)
{
	clones[5] += (is_sphere == false);
	return (1);
}

int	check_height(t_shape *shape, char *str, double *num)
{
	double	res;

	if (!is_double(str))
		return (1);
	if (!num)
	{
		res = str_to_double(str);
		if (res < 0 || res < 0)
			return (1);
		shape->h = res;
		return (0);
	}
	*num = str_to_double(str);
	if (*num < 0 || *num < 0)
		return (1);
	shape->h = (*num);
	return (0);
}

char	*trimline(char *str)
{
	int		i;
	char	*temp;

	i = -1;
	temp = str;
	while (temp && temp[++i])
	{
		if (temp[i] == '\t' || temp[i] == '\n')
			temp[i] = ' ';
	}
	str = ft_strtrim(temp, " ");
	free(temp);
	return (str);
}
