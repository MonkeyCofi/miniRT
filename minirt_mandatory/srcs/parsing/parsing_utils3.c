/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:35:15 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 19:25:01 by pipolint         ###   ########.fr       */
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
	m->object_count++;
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

int	check_magnitude(t_minirt *m, t_tuple *vector, char *line)
{
	if (is_equal(magnitude(vector), 0))
		return (0);
	if (is_equal(magnitude(vector), 1) == false)
	{
		write_check(m, "Line: ");
		write_check(m, line);
		write_check(m, " is not normalized\n");
		write_check(m, "Normalizing vector\n");
	}
	return (1);
}
