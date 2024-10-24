/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:02:04 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 17:37:04 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

void	set_vector_points(t_tuple *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 0;
}

void	set_point_points(t_tuple *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
	v->w = 1;
}

t_tuple	return_tuple(double x, double y, double z, double w)
{
	t_tuple	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	ret.w = w;
	return (ret);
}

t_tuple	*return_tuple_pointer(double x, double y, double z, double w)
{
	t_tuple	*ret;

	ret = ft_calloc(1, sizeof(t_tuple));
	if (!ret)
		return (NULL);
	ret->x = x;
	ret->y = y;
	ret->z = z;
	ret->w = w;
	return (ret);
}

t_ray	create_ray_static(t_tuple origin, t_tuple direction)
{
	t_ray	ray;

	ray.origin.x = origin.x;
	ray.origin.y = origin.y;
	ray.origin.z = origin.z;
	ray.origin.w = origin.w;
	ray.direction.x = direction.x;
	ray.direction.y = direction.y;
	ray.direction.z = direction.z;
	ray.direction.w = direction.w;
	return (ray);
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
