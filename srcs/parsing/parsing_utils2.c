/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:30:08 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/03 20:24:31 by pipolint         ###   ########.fr       */
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

int	check_ulong(char *str, double *num)
{
	if (!isulong(str))
		return (1);
	*num = ft_atoi(str);
	if (*num > 180 || *num < 0)
		return (1);
	return (0);
}

int	check_double(char *str, double *num, t_bool check_boundary)
{
	if (!is_double(str))
		return (1);
	*num = str_to_double(str);
	if (check_boundary == true)
	{
		if (*num > 1 || *num < 0)
			return (1);
	}
	return (0);
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
		&& minirt->light_count > 0)
		return (1);
	return (0);
}
