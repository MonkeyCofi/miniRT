/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/30 11:18:00 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define MIN_T_DIFFERENCE 0.0001

t_cylinder	*create_cylinder(t_minirt *m)
{
	t_cylinder	*cyl;

	cyl = calloc_and_check(sizeof(t_cylinder), 1, m, CYL_ERR);
	cyl->point = return_point(0, 0, 0);
	cyl->radius = 1;
	cyl->type = CYLINDER;
	cyl->minimum = 0;
	cyl->maximum = INFINITY;
	cyl->is_closed = true;
	return (cyl);
}

t_tuple	normal_pos_cylinder(t_shape *shape, t_tuple pos)
{
	t_cylinder	*cylinder;
	double		distance;

	cylinder = shape->shape;
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < cylinder->radius && (pos.y >= cylinder->maximum - EPSILON))
		return (return_vector(0, 1, 0));
	else if (distance < cylinder->radius && (pos.y <= cylinder->minimum + \
	EPSILON))
		return (return_vector(0, -1, 0));
	return (return_vector(pos.x, 0, pos.z));
}

static t_bool	at_cap(t_ray *ray, double t, t_cylinder *c)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	if (((x * x) + (z * z) <= (c->radius * c->radius))
		&& (ray->origin.y + t * ray->direction.y >= c->minimum \
		&& ray->origin.y + t * ray->direction.y <= c->maximum))
		return (true);
	return (false);
}

t_bool	cylinder_end_hit(t_cylinder *cylinder, t_shape *shape_ptr, \
t_ray *ray, t_intersects *intersects)
{
	double	t;

	if (cylinder->is_closed == 0)
		return (false);
	if (fabs(ray->direction.y) > EPSILON)
	{
		if (ray->direction.y != 0)
		{
			t = (cylinder->minimum - ray->origin.y) / ray->direction.y;
			if (t > cylinder->minimum && at_cap(ray, t, cylinder))
				add_to_intersect(t, shape_ptr, intersects);
			t = (cylinder->maximum - ray->origin.y) / ray->direction.y;
			if (t > cylinder->minimum && t <= cylinder->maximum && at_cap(\
			ray, t, cylinder))
				add_to_intersect(t, shape_ptr, intersects);
		}
	}
	return (true);
}
