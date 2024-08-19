/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:57:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/08/19 19:28:59 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_vector_points(t_vector *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

t_vector	add_vectors(t_vector *vec1, t_vector *vec2)
{
	t_vector	vec;

	vec.x = vec1->x + vec2->x;
	vec.y = vec1->y = vec2->y;
	vec.z = vec1->z = vec2->z;
	return (vec);
}

t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2)
{
	t_vector	resultant;

	resultant.x = vec2->x - vec1->x;
	resultant.y = vec2->y - vec1->y;
	resultant.z = vec2->z - vec1->z;
	return (resultant);
}

void	scalar(t_vector *vec, double scalar)
{
	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;
}

t_vector	return_scalar(t_vector *vec, double scalar)
{
	t_vector	resultant;
	
	resultant.x = vec->x * scalar;
	resultant.y = vec->y * scalar;
	resultant.z = vec->z * scalar;
	return (resultant);
}

double dot_product(t_vector *vec1, t_vector *vec2)
{
	return ((vec1->x * vec2->x) + (vec1->y * vec2->y) + (vec1->z * vec2->z));
}

void normalize(t_vector *vector)
{
	double	magnitude;

	magnitude = sqrt(dot_product(vector, vector));
	vector->x /= magnitude;
	vector->y /= magnitude;
	vector->z /= magnitude;
}