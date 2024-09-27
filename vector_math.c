/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:57:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/27 12:57:44 by pipolint         ###   ########.fr       */
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
