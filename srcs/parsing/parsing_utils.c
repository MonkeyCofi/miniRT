/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 08:48:18 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/21 11:15:14 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	dovector(char *string, t_tuple *calc)
{
	char	**str;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	str = ft_split(string, ',');
	while (str && str[++i])
	{
		if (!is_double(str[i]))
			ret = 1;
	}
	if (arr_len(str) != 3)
		ret = 1;
	else
	{
		calc->x = str_to_double(str[0]);
		calc->y = str_to_double(str[1]);
		calc->z = str_to_double(str[2]);
	}
	free_arr(str);
	return (ret);
}

void	orientationnormalize(t_tuple *calc)
{
	calc->x = ((calc->x + 1) / 2) * 360;
	calc->y = ((calc->y + 1) / 2) * 360;
	calc->z = ((calc->z + 1) / 2) * 360;
}

int	dovectororientation(char *string, t_tuple *calc)
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
	else if (ret == 0)
	{
		calc->x = str_to_double(str[0]);
		calc->y = str_to_double(str[1]);
		calc->z = str_to_double(str[2]);
	}
	if ((calc->x > 1 || calc->x < -1)
		|| (calc->y > 1 || calc->y < -1)
		|| (calc->z > 1 || calc->z < -1))
		ret = 1;
	free_arr(str);
	normalize(calc);
	return (ret);
}

int	dovectororientationf(char *string, t_tuple *calc)
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
	else if (ret == 0)
	{
		calc->x = str_to_double(str[0]);
		calc->y = str_to_double(str[1]);
		calc->z = str_to_double(str[2]);
	}
	if ((calc->x > 1 || calc->x < -1)
		|| (calc->y > 1 || calc->y < -1)
		|| (calc->z > 1 || calc->z < -1))
		ret = 1;
	free_arr(str);
	return (ret);
}

int	dovectorcolor(char *string, t_tuple *calc)
{
	char	**str;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	str = ft_split(string, ',');
	(void)calc;
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
	if ((calc->x > 1 || calc->x < -1)
		|| (calc->y > 1 || calc->y < -1)
		|| (calc->z > 1 || calc->z < -1))
		ret = 1;
	free_arr(str);
	return (ret);
}
