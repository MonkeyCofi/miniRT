/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/19 20:54:34 by pipolint         ###   ########.fr       */
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

t_tuple	*normal_pos_cylinder(t_cylinder *cylinder, t_tuple pos)
{
	t_tuple		*normal;
	t_tuple		*world_normal;
	float		distance;

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
	world_normal = tuple_mult(transpose(cylinder->inverse), &pos);
	world_normal->w = 0;
	normalize(world_normal);
	return (world_normal);
}

static t_bool	at_cap(t_ray *ray, float radius, float t)
{
	float	x;
	float	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return ((x * x) + (z * z) <= radius * radius);
}

t_bool	cylinder_end_hit(t_cylinder *cylinder, t_ray *ray, t_intersects *intersects)
{
	float	t;

	if (cylinder->is_closed == false || is_equal(ray->direction.y, 0))
		return (false);
	t = (cylinder->minimum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cylinder->radius))
	{
		if (add_to_intersect(t, intersects, CYLINDER, cylinder, cylinder->material) == false)
			return (true);
	}
	t = (cylinder->maximum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cylinder->radius))
		add_to_intersect(t, intersects, CYLINDER, cylinder, cylinder->material);
	return (true);
}

t_bool	cylinder_hit(t_minirt *m, int index, t_intersects *intersects, t_ray *ray, t_cylinder *cyl)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t[3];
	float	tt[2];
	t_tuple	points[2];
	//t_4dmat	*inverse;
	t_ray	*inverse_ray;

	//if (!cyl->inverse)
	//{
	//	if (inverse_mat(m->shapes[index]->inverse_mat, &inverse) == error)
	//		return (error);
	//	if (!inverse)
	//		return (false);
	//	cyl->inverse = inverse;
	//	points[0] = tuple_mult_fast(m->shapes[index]->inverse_mat, &ray->origin);
	//	points[1] = tuple_mult_fast(m->shapes[index]->inverse_mat, &ray->direction);
	//	inverse_ray = create_ray(points[0], points[1]);
	//}
	//else
	//	inverse_ray = create_ray(ray->origin, ray->direction);
	
	points[0] = tuple_mult_fast(m->shapes[index]->inverse_mat, &ray->origin);
	points[1] = tuple_mult_fast(m->shapes[index]->inverse_mat, &ray->direction);
	inverse_ray = create_ray(points[0], points[1]);
	
	a = (inverse_ray->direction.x * inverse_ray->direction.x) + (inverse_ray->direction.z * inverse_ray->direction.z);
	if (is_equal(a, 0))
		return (cylinder_end_hit(cyl, inverse_ray, intersects));
	b = (2 * inverse_ray->origin.x * inverse_ray->direction.x) + (2 * inverse_ray->origin.z * inverse_ray->direction.z);
	c = (inverse_ray->origin.x * inverse_ray->origin.x) + (inverse_ray->origin.z * inverse_ray->origin.z) - 1;
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
	tt[0] = inverse_ray->origin.y + t[0] * inverse_ray->direction.y;
	if (cyl->minimum < tt[0] && tt[0] < cyl->maximum)
	{
		if (add_to_intersect(t[0], intersects, CYLINDER, cyl, cyl->material) == false)
			return (true);
	}
	tt[1] = inverse_ray->origin.y + t[1] * inverse_ray->direction.y;
	if (cyl->minimum < tt[1] && tt[1] < cyl->maximum)
		add_to_intersect(t[1], intersects, CYLINDER, cyl, cyl->material);
	cylinder_end_hit(cyl, inverse_ray, intersects);
	(void)m;
	return (true);
}
