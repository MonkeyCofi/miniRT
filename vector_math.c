/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 15:57:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/26 22:25:13 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	add_vectors(t_vector *vec1, t_vector *vec2)
{
	t_vector	vec;

	vec.x = vec1->x + vec2->x;
	vec.y = vec1->y + vec2->y;
	vec.z = vec1->z + vec2->z;
	vec.w = vec1->w + vec2->w;
	return (vec);
}

t_vector	subtract_vectors(t_vector *vec1, t_vector *vec2)
{
	t_vector	resultant;

	resultant.x = vec2->x - vec1->x;
	resultant.y = vec2->y - vec1->y;
	resultant.z = vec2->z - vec1->z;
	resultant.w = vec2->w - vec1->w;
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

t_vector	return_at(t_ray *ray, double t)
{
	t_vector	new;

	new = return_scalar(&ray->direction, t);
	return (add_vectors(&ray->origin, &new));
}
