/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/22 18:38:32 by pipolint         ###   ########.fr       */
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

t_tuple	*normal_pos_cylinder(t_shape *shape, t_tuple pos)
{
	t_tuple		*normal;
	t_cylinder	*cylinder;
	t_tuple		*world_normal;
	t_4dmat		*transpose_inv;
	double		distance;

	cylinder = shape->shape;
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < 1 && pos.y >= cylinder->maximum - EPSILON)
		return (return_tuple_pointer(0, 1, 0, VECTOR));
	else if (distance < 1 && pos.y <= cylinder->minimum + EPSILON)
		return (return_tuple_pointer(0, -1, 0, VECTOR));
	normal = ft_calloc(1, sizeof(t_tuple));
	normal->x = pos.x;
	normal->y = 0;
	normal->z = pos.z;
	normal->w = VECTOR;
	transpose_inv = transpose(shape->inverse_mat);
	world_normal = tuple_mult(transpose_inv, &pos);
	world_normal->w = 0;
	normalize(world_normal);
	free(transpose_inv);
	return (world_normal);
}

static t_bool	at_cap(t_ray *ray, double radius, double t)
{
	double	x;
	double	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return ((x * x) + (z * z) <= radius * radius);
}

static t_bool	cylinder_end_hit(t_cylinder *cylinder, t_shape *shape_ptr, t_ray *ray, t_intersects *intersects)
{
	double	t;

	if (cylinder->is_closed == false || is_equal(ray->direction.y, 0))
		return (false);
	t = (cylinder->minimum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cylinder->radius))
	{
		if (add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder, cylinder->material) == false)
			return (true);
	}
	t = (cylinder->maximum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cylinder->radius))
		add_to_intersect(t, shape_ptr, intersects, CYLINDER, cylinder, cylinder->material);
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
	if (is_equal(a, 0))
		return (cylinder_end_hit(cyl, m->shapes[shape_index], ray, intersects));
	b = (2 * ray->origin.x * ray->direction.x) + (2 * ray->origin.z * ray->direction.z);
	c = (ray->origin.x * ray->origin.x) + (ray->origin.z * ray->origin.z) - 1;
	disc = (b * b) - (4 * a * c);
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
	(void)m;
	return (true);
}
