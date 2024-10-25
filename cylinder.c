/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/25 15:50:02 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cylinder	*create_cylinder(t_tuple orientation)
{
	t_cylinder	*cyl;

	cyl = ft_calloc(1, sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	cyl->transform = identity();
	cyl->point = return_tuple(0, 0, 0, POINT);
	cyl->radius = 1;
	cyl->inverse = NULL;
	cyl->material = create_default_material();
	cyl->type = CYLINDER;
	cyl->orientation = return_tuple(orientation.x, orientation.y, orientation.z, orientation.w);
	cyl->minimum = -INFINITY;
	cyl->maximum = INFINITY;
	cyl->is_closed = false;
	return (cyl);
}

t_tuple	normal_pos_cylinder(t_shape *shape, t_tuple pos)
{
	t_cylinder	*cylinder;
	double		distance;

	cylinder = shape->shape;
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < 1 && (pos.y > cylinder->maximum - EPSILON || is_equal(pos.y, cylinder->maximum - EPSILON)))
		return (return_vector(0, 1, 0));
	else if (distance < 1 && (pos.y < cylinder->minimum + EPSILON || is_equal(pos.y, cylinder->minimum + EPSILON)))
		return (return_vector(0, -1, 0));
	return (return_vector(pos.x, 0, pos.z));
}

static int	at_cap(t_ray *ray, double radius, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	(void)radius;
	return (((x * x) + (z * z)) <= 1);
}

static t_bool	cylinder_end_hit(t_cylinder *cylinder, t_shape *shape_ptr, t_ray *ray, t_intersects *intersects)
{
	double	t;

	if (cylinder->is_closed == false || ray->direction.y < EPSILON || is_equal(ray->direction.y, 0))
		return (false);
	if (fabs(ray->direction.y) > EPSILON)
	{
		t = (cylinder->minimum - ray->origin.y) / ray->direction.y;
		if (at_cap(ray, t, cylinder->radius))
		{
			if (add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder, cylinder->material) == false)
				return (true);
		}
		t = (cylinder->maximum - ray->origin.y) / ray->direction.y;
		if (at_cap(ray, t, cylinder->radius))
			add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder, cylinder->material);
	}
	return (true);
}

t_bool	intersect_cylinder(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index)
{
	t_cylinder	*cyl;
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t[3];
	double		tt[2];
	
	cyl = m->shapes[shape_index]->shape;
	a = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z);
	if (a < EPSILON)
	{
		cylinder_end_hit(cyl, m->shapes[shape_index], ray, intersects);
		return (false);
	}
	b = (2 * ray->origin.x * ray->direction.x) + (2 * ray->origin.z * ray->direction.z);
	c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z - 1;
	disc = (b * b) - (4 * a * c);
	if (disc < 0)
		return (false);
	a *= 2;
	b *= -1;
	disc = sqrt(disc);
	t[0] = (b - disc) / (a);
	t[1] = (b + disc) / (a);
	if (t[0] > t[1])
	{
		t[2] = t[0];
		t[0] = t[1];
		t[1] = t[2];
	}
	tt[0] = ray->origin.y + t[0] * ray->direction.y;
	if (cyl->minimum < tt[0] && tt[0] < cyl->maximum)
	{
		if (add_to_intersect(t[0], m->shapes[shape_index], intersects, CYLINDER, cyl, cyl->material) == false)
			return (true);
	}
	tt[1] = ray->origin.y + t[1] * ray->direction.y;
	if (cyl->minimum < tt[1] && tt[1] < cyl->maximum)
		add_to_intersect(t[1], m->shapes[shape_index], intersects, CYLINDER, cyl, cyl->material);
	cylinder_end_hit(cyl, m->shapes[shape_index], ray, intersects);
	return (true);
}
