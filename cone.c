/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:06:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/16 22:23:33 by pipolint         ###   ########.fr       */
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
	cone->transform = identity();
	cone->inverse = NULL;
	cone->type = CONE;
	cone->minimum = -INFINITY;
	cone->maximum = INFINITY;
	cone->is_closed = false;
	return (cone);
}

//static inline t_bool	at_cap(t_ray *ray, float t)
//{
//	float	x;
//	float	y;
//	float	z;

//	if (ray->direction.y == 0)
//		return (false);
//	y = -(ray->origin.y / ray->direction.y);
//	x = ray->origin.x + t * ray->direction.x;
//	z = ray->origin.z + t * ray->direction.z;
//	return ((x * x) + (z * z) <= (y * y));
//}

static inline t_bool	at_cap(t_ray *ray, float t, float min_max)
{
	float	x;
	float	y;
	float	z;

	if (ray->direction.y == 0)
		return (false);
	y = -(ray->origin.y / ray->direction.y);
	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return ((x * x) + (z * z) <= (min_max * min_max));
}

t_tuple	*normal_pos_cone(t_cone *cone, t_tuple pos)
{
	float		distance;
	float		y;
	
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < 1 && pos.y >= cone->maximum - EPSILON)
		return (return_tuple_pointer(0, 1, 0, VECTOR));
	else if (distance < 1 && pos.y <= cone->minimum + EPSILON)
		return (return_tuple_pointer(0, -1, 0, VECTOR));
	y = sqrt((pos.x * pos.x) + (pos.z * pos.z));
	if (y > 0)
		y = -y;
	return (return_tuple_pointer(pos.x, y, pos.z, VECTOR));
}

t_bool	cone_end_hit(t_cone *cone, t_ray *ray, t_intersects *intersects)
{
	float	t;
	
	if (cone->is_closed == false || is_equal(ray->direction.y, 0))
		return (false);
	t = (cone->minimum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cone->minimum))
	{
		intersects->intersections[intersects->intersection_count].t = t;
		intersects->intersections[intersects->intersection_count].shape = cone;
		intersects->intersections[intersects->intersection_count].type = CONE;
		intersects->intersections[intersects->intersection_count].material = cone->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
		else
			return (true);
	}
	t = (cone->maximum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cone->maximum))
	{
		intersects->intersections[intersects->intersection_count].t = t;
		intersects->intersections[intersects->intersection_count].shape = cone;
		intersects->intersections[intersects->intersection_count].type = CONE;
		intersects->intersections[intersects->intersection_count].material = cone->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
	}
	return (true);
}

t_bool	cone_hit(t_cone *cone, t_ray *ray, t_intersects *intersects)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t[3];
	float	y[2];
	
	a = (ray->direction.x * ray->direction.x) - (ray->direction.y * ray->direction.y) + (ray->direction.z * ray->direction.z);
	b = (2 * ray->origin.x * ray->direction.x) - (2 * ray->origin.y * ray->direction.y) + (2 * ray->origin.z * ray->direction.z);
	c = (ray->origin.x * ray->origin.x) - (ray->origin.y * ray->origin.y) + (ray->origin.z * ray->origin.z);
	if (is_equal(a, 0))
	{
		if (is_equal(b, 0))
			return (false);
		intersects->intersections[intersects->intersection_count].t = -c / (2 * b);
		intersects->intersections[intersects->intersection_count].shape = cone;
		intersects->intersections[intersects->intersection_count].type = CONE;
		intersects->intersections[intersects->intersection_count].material = cone->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
		else
			return (true);
	}
	disc = (b * b) - 4 * a * c;
	if (disc < 0)
		return (false);
	t[0] = (-b - sqrt(disc)) / (2 * a);
	t[1] = (-b + sqrt(disc)) / (2 * a);
	if (t[0] > t[1])
	{
		t[2] = t[0];
		t[0] = t[1];
		t[1] = t[2];
	}
	y[0] = ray->origin.y + t[0] * ray->direction.y;
	if (y[0] > cone->minimum && y[0] < cone->maximum)
	{
		intersects->intersections[intersects->intersection_count].t = t[0];
		intersects->intersections[intersects->intersection_count].shape = cone;
		intersects->intersections[intersects->intersection_count].type = CONE;
		intersects->intersections[intersects->intersection_count].material = cone->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
		else
			return (true);
	}
	y[1] = ray->origin.y + t[1] * ray->direction.y;
	if (y[1] > cone->minimum && y[1] < cone->maximum)
	{
		intersects->intersections[intersects->intersection_count].t = t[1];
		intersects->intersections[intersects->intersection_count].shape = cone;
		intersects->intersections[intersects->intersection_count].type = CONE;
		intersects->intersections[intersects->intersection_count].material = cone->material;
		if (intersects->intersection_count < MAX_INTERSECTS)
			intersects->intersection_count++;
	}
	cone_end_hit(cone, ray, intersects);
	return (true);
}
