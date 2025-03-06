/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:52:53 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 14:52:59 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	position(t_ray *ray, double t)
{
	t_tuple	ret;

	set_point_points(&ret, \
		(ray->direction.x * t) + ray->origin.x, \
		(ray->direction.y * t) + ray->origin.y, \
		(ray->direction.z * t) + ray->origin.z);
	return (ret);
}

t_bool	add_to_intersect(double t, t_shape *shape, t_intersects *intersects)
{
	if (intersects->intersection_count < MAX_INTERSECTS)
	{
		intersects->intersections[intersects->intersection_count].t = t;
		intersects->intersections[intersects->intersection_count].type = \
																	shape->type;
		intersects->intersections[intersects->intersection_count].shape = \
																shape->shape;
		intersects->intersections[intersects->intersection_count].material = \
																shape->material;
		intersects->intersections[intersects->intersection_count].shape_ptr = \
																		shape;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
		else
			return (false);
	}
	return (true);
}
