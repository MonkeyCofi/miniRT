/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:06:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/29 11:56:08 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cone	*create_cone()
{
	t_cone	*cone;
	
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (NULL);
	cone->point = return_tuple(0, 0, 0, POINT);
	cone->material = create_default_material();
	cone->type = CONE;
	cone->minimum = -INFINITY;
	cone->maximum = INFINITY;
	cone->is_closed = false;
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

static inline t_bool	at_cap(t_ray *ray, double t, double min_max)
{
	double	x;
	// double	y;
	double	z;

	if (ray->direction.y == 0)
		return (false);
	x = ray->origin.x + t * ray->direction.x;
	// y = -(ray->origin.y / ray->direction.y);
	z = ray->origin.z + t * ray->direction.z;
	return ((x * x) + (z * z) <= (min_max * min_max));
}

t_tuple	normal_pos_cone(t_shape *shape, t_tuple pos)
{
	t_cone		*cone;
	double		distance;
	double		y;

	cone = shape->shape;
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < 1 && (pos.y > cone->maximum - EPSILON || is_equal(pos.y, cone->maximum - EPSILON)))
		return (return_vector(0, 1, 0));
	else if (distance < 1 && (pos.y < cone->minimum + EPSILON || is_equal(pos.y, cone->minimum + EPSILON)))
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
	if (at_cap(ray, t, cone->minimum))
	{
		if (add_to_intersect(t, shape_ptr, intersects, CONE, cone) == false)
			return (true);
	}
	t = (cone->maximum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cone->maximum))
		add_to_intersect(t, shape_ptr, intersects, CONE, cone);
	return (true);
}

t_bool	intersect_cone(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index)
{
	t_cone	*cone;
	double	a;
	double	b;
	double	c;
	double	disc;
	double	t[2];
	double	y[2];

	cone = m->shapes[shape_index]->shape;
	a = (ray->direction.x * ray->direction.x) - (ray->direction.y * ray->direction.y) + (ray->direction.z * ray->direction.z);
	b = (2 * ray->origin.x * ray->direction.x) - (2 * ray->origin.y * ray->direction.y) + (2 * ray->origin.z * ray->direction.z);
	c = (ray->origin.x * ray->origin.x) - (ray->origin.y * ray->origin.y) + (ray->origin.z * ray->origin.z);
	if (is_equal(a, 0))
	{
		if (is_equal(b, 0))
			return (false);
		if (add_to_intersect(-c / (2 * b), m->shapes[shape_index], intersects, CONE, cone) == false)
			return (true);
	}
	disc = (b * b) - 4 * a * c;
	if (disc < 0)
		return (false);
	a *= 2;
	b *= -1;
	t[0] = (b - sqrt(disc)) / (a);
	t[1] = (b + sqrt(disc)) / (a);
	y[0] = ray->origin.y + t[0] * ray->direction.y;
	if (y[0] > cone->minimum && y[0] < cone->maximum)
	{
		if (add_to_intersect(t[0], m->shapes[shape_index], intersects, CONE, cone) == false)
			return (true);
	}
	y[1] = ray->origin.y + t[1] * ray->direction.y;
	if (y[1] > cone->minimum && y[1] < cone->maximum)
		add_to_intersect(t[1], m->shapes[shape_index], intersects, CONE, cone);
	cone_end_hit(m->shapes[shape_index], ray, intersects);
	return (true);
}
