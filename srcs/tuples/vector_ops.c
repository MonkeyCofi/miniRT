/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:28:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/25 19:15:41 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	dot_product(t_tuple *vec1, t_tuple *vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}

t_tuple	cross_product(t_tuple *vec1, t_tuple *vec2)
{
	t_tuple	cross;
	double	x;
	double	y;
	double	z;

	ft_bzero(&cross, sizeof(t_tuple));
	x = vec1->y * vec2->z - vec1->z * vec2->y;
	y = vec1->z * vec2->x - vec1->x * vec2->z;
	z = vec1->x * vec2->y - vec1->y * vec2->x;
	set_vector_points(&cross, x, y, z);
	return (cross);
}

void	normalize(t_tuple *vector)
{
	double	magnitude;

	magnitude = sqrt(((vector->x * vector->x) + (vector->y * vector->y) + \
		(vector->z * vector->z)));
	if (magnitude > EPSILON)
	{
		vector->x /= magnitude;
		vector->y /= magnitude;
		vector->z /= magnitude;
	}
	else
	{
		vector->x = 0;
		vector->y = 0;
		vector->z = 0;
	}
}

double	magnitude(t_tuple *vector)
{
	double	a;
	double	b;
	double	c;

	a = vector->x * vector->x;
	b = vector->y * vector->y;
	c = vector->z * vector->z;
	return (sqrt((a + b + c)));
}

void	negate(t_tuple *to_negate)
{
	to_negate->x = -(to_negate->x);
	to_negate->y = -(to_negate->y);
	to_negate->z = -(to_negate->z);
}
