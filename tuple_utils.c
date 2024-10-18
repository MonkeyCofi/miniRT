/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:02:04 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/19 02:28:21 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

void	set_vector_points(t_tuple *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 0;
}

void	set_point_points(t_tuple *v, float x, float y, float z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1;
}

t_tuple	return_tuple(float x, float y, float z, float w)
{
	t_tuple	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
	return (ret);
}

t_tuple	*return_tuplepoint(float x, float y, float z, float w)
{
	t_tuple	*ret = ft_calloc(1, sizeof(t_tuple));

	ret->x = x;
	ret->y = y;
	ret->z = z;
	ret->w = w;
	return (ret);
}

t_ray	*create_ray(t_tuple origin, t_tuple direction)
{
	t_ray	*ray;
	
	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->origin = return_tuple(origin.x, origin.y, origin.z, 1);
	ray->direction = return_tuple(direction.x, direction.y, direction.z, 0);
	return (ray);
}
