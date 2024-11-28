/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:11:56 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 19:13:07 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	return_colorf(double r, double g, double b)
{
	t_tuple	ret;

	ret.r = r;
	ret.g = g;
	ret.b = b;
	ret.w = COLOR;
	return (ret);
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
	ray.origin.w = POINT;
	ray.direction.x = direction.x;
	ray.direction.y = direction.y;
	ray.direction.z = direction.z;
	ray.direction.w = VECTOR;
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
