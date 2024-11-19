/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:57:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/19 09:42:17 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	add_vectors(t_tuple *vec1, t_tuple *vec2)
{
	t_tuple	vec;

	vec.x = vec1->x + vec2->x;
	vec.y = vec1->y + vec2->y;
	vec.z = vec1->z + vec2->z;
	vec.w = vec1->w + vec2->w;
	return (vec);
}

t_tuple	multiply_tuples(t_tuple *tup1, t_tuple *tup2, int tuple_type)
{
	t_tuple	ret_tup;

	ret_tup.x = tup1->x * tup2->x;
	ret_tup.y = tup1->y * tup2->y;
	ret_tup.z = tup1->z * tup2->z;
	ret_tup.w = tuple_type;
	return (ret_tup);
}

t_tuple	subtract_tuples(t_tuple *vec1, t_tuple *vec2)
{
	t_tuple	resultant;

	resultant.x = vec2->x - vec1->x;
	resultant.y = vec2->y - vec1->y;
	resultant.z = vec2->z - vec1->z;
	resultant.w = vec2->w - vec1->w;
	return (resultant);
}

void	scalar(t_tuple *vec, double scalar)
{
	vec->x *= scalar;
	vec->y *= scalar;
	vec->z *= scalar;
}

t_tuple	return_scalar(t_tuple *vec, double scalar)
{
	t_tuple	resultant;
	
	resultant.x = vec->x * scalar;
	resultant.y = vec->y * scalar;
	resultant.z = vec->z * scalar;
	return (resultant);
}

t_tuple	return_at(t_ray *ray, double t)
{
	t_tuple	new;

	new = return_scalar(&ray->direction, t);
	return (add_vectors(&ray->origin, &new));
}

// this works diff than u expect it to sorry bout dat, matrix res into b is = a;

void	matrix_cross(t_tuple *a, t_tuple *b, t_4dmat res)
{
	a->x = b->x * res.matrix[0][0] + b->y * res.matrix[1][0] + b->z * res.matrix[2][0] + b->w * res.matrix[3][0];
	a->y = b->x * res.matrix[0][1] + b->y * res.matrix[1][1] + b->z * res.matrix[2][1] + b->w * res.matrix[3][1];
	a->z = b->x * res.matrix[0][2] + b->y * res.matrix[1][2] + b->z * res.matrix[2][2] + b->w * res.matrix[3][2];
	a->w = b->x * res.matrix[0][3] + b->y * res.matrix[1][3] + b->z * res.matrix[2][3] + b->w * res.matrix[3][3];
}
