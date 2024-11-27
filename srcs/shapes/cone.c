/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:06:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/26 17:28:34 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cone	*create_cone(t_minirt *m)
{
	t_cone	*cone;

	cone = calloc_and_check(sizeof(t_cone), 1, m, CON_ERR);
	cone->point = return_tuple(0, 0, 0, POINT);
	cone->material = create_default_material();
	cone->type = CONE;
	cone->minimum = -INFINITY;
	cone->maximum = INFINITY;
	cone->is_closed = true;
	return (cone);
}

//static inline t_bool	at_cap(t_ray *ray, double t)
//{
//	double	x;
//	double	y;
//	double	z;

//	if (ray->direction.y == 0)
//		return (false);
//	y = -(ray->origin.y / ray->direction.y);
//	x = ray->origin.x + t * ray->direction.x;
//	z = ray->origin.z + t * ray->direction.z;
//	return ((x * x) + (z * z) <= (y * y));
//}

// static t_bool	at_cap(t_ray *ray, double t, t_cylinder *c)
// {
// 	double	x;
// 	double	z;

// 	x = ray->origin.x + t * ray->direction.x;
// 	z = ray->origin.z + t * ray->direction.z;
// 	if (((x * x) + (z * z) <= (c->radius * c->radius))
// 		&& (ray->origin.y + t * ray->direction.y >= c->minimum \
// 		&& ray->origin.y + t * ray->direction.y <= c->maximum))
// 		return (true);
// 	return (false);
// }

static inline t_bool	at_cap(t_ray *ray, double t, t_cone *cone, double y)
{
	double x;
	double z;
	double radius;

	x = ray->origin.x + t * ray->direction.x;
    z = ray->origin.z + t * ray->direction.z;
    radius = (cone->maximum - y) / (cone->maximum - cone->minimum);
    return ((x * x) + (z * z) <= (radius * radius));
}

t_tuple	normal_pos_cone(t_shape *shape, t_tuple pos)
{
	t_cone		*cone;
	double		distance;
	double		y;

	cone = shape->shape;
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < 1 && (pos.y > cone->maximum - EPSILON || is_equal(pos.y, \
	cone->maximum - EPSILON)))
		return (return_vector(0, 1, 0));
	else if (distance < 1 && (pos.y < cone->minimum + EPSILON || is_equal(\
	pos.y, cone->minimum + EPSILON)))
		return (return_vector(0, -1, 0));
	y = sqrt(distance);
	if (pos.y > 0)
		y = -y;
	return (return_vector(pos.x, y, pos.z));
}

t_bool	cone_end_hit(t_shape *shape_ptr, t_ray *ray, t_intersects *intersects)
{
	t_cone	*cone;
	double	t;

	cone = shape_ptr->shape;
	if (cone->is_closed == false || is_equal(ray->direction.y, 0))
		return (false);
	t = (cone->minimum - ray->origin.y) / ray->direction.y;
	if (t > cone->minimum && at_cap(ray, t, cone, cone->minimum))
	{
		if (add_to_intersect(t, shape_ptr, intersects, CONE, cone) == false)
			return (true);
	}
	t = (cone->maximum - ray->origin.y) / ray->direction.y;
	if ( at_cap(ray, t, cone, cone->maximum))
		add_to_intersect(t, shape_ptr, intersects, CONE, cone);
	return (true);
}

