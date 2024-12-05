/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:35:15 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/05 19:58:49 by pipolint         ###   ########.fr       */
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
