/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:30:08 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/05 19:58:54 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	isulong(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	rt_file(char *str)
{
	int	len;

	len = ft_strlen(str) - 3;
	if (len > 3)
		return ((ft_strncmp((str + len), ".rt", 3) == 0));
	return (0);
}

int	invalidfile(t_minirt *minirt)
{
	if (minirt->ambient->flag == 1 && minirt->cam->flag == 1
		&& minirt->light->found)
		return (1);
	return (0);
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
