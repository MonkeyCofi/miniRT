/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:28:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/23 17:47:39 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	set_vector_points(t_vector *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

double dot_product(t_vector *vec1, t_vector *vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}

t_vector	cross_product(t_vector *vec1, t_vector *vec2)
{
	t_vector	cross;

	ft_bzero(&cross, sizeof(t_vector));
	(void)vec1;
	(void)vec2;
	return (cross);
}

void normalize(t_vector *vector)
{
	double	magnitude;

	magnitude = sqrt(dot_product(vector, vector));
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}

void	negate(t_vector *to_negate)
{
	to_negate->x *= -1;
	to_negate->y *= -1;
	to_negate->z *= -1;
}