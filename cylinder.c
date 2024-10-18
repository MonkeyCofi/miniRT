/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/18 20:25:44 by pipolint         ###   ########.fr       */
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
	(void)cylinder;
	return (normal);
}

static t_bool	at_cap(t_ray *ray, float t)
{
	float	x;
	float	z;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	return ((x * x) + (z * z) <= 1);
}

t_bool	cylinder_end_hit(t_cylinder *cylinder, t_ray *ray, t_intersects *intersects)
{
	float	t;

	if (cylinder->is_closed == false || is_equal(ray->direction.y, 0))
		return (false);
	t = (cylinder->minimum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t))
	{
		if (add_to_intersect(t, intersects, CYLINDER, cylinder, cylinder->material) == false)
			return (true);
	}
	t = (cylinder->maximum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t))
		add_to_intersect(t, intersects, CYLINDER, cylinder, cylinder->material);
	return (true);
}

//t_bool	cylinder_hit(t_minirt *m, t_intersects *intersects, t_ray *ray, t_cylinder *cyl)
//{
//	float	a;
//	float	b;
//	float	c;
//	float	disc;
//	float	t[3];
//	float	tt[2];
//	t_4dmat	*inverse;
//	t_ray	inverse_ray;

//	if (!cyl->inverse)
//	{
//		if (inverse_mat(&cyl->transform, &inverse) == error)
//			return (error);
//		if (!inverse)
//			return (false);
//		cyl->inverse = inverse;
//		inverse_ray.origin = tuple_mult_fast(cyl->inverse, &ray->origin);
//		inverse_ray.direction = tuple_mult_fast(cyl->inverse, &ray->direction);
//	}
//	a = (ray->direction.x * ray->direction.x) + (ray->direction.z * ray->direction.z);
//	if (is_equal(a, 0))
//		return (cylinder_end_hit(cyl, ray, intersects));
//	b = 2 * (ray->origin.x * ray->direction.x) + 2 * (ray->origin.z * ray->direction.z);
//	c = (ray->origin.x * ray->origin.x) + (ray->origin.z * ray->origin.z) - 1;
//	disc = (b * b) - 4 * a * c;
//	if (disc < 0)
//		return (false);
//	t[0] = (-b - sqrt(disc)) / (2 * a);
//	t[1] = (-b + sqrt(disc)) / (2 * a);
//	if (t[0] > t[1])
//	{
//		t[2] = t[0];
//		t[0] = t[1];
//		t[1] = t[2];
//	}
//	tt[0] = ray->origin.y + t[0] * ray->direction.y;
//	if (cyl->minimum < tt[0] && tt[0] < cyl->maximum)
//	{
//		//printf("true\n");
//		intersects->intersections[intersects->intersection_count].t = t[0];
//		intersects->intersections[intersects->intersection_count].shape = cyl;
//		intersects->intersections[intersects->intersection_count].type = CYLINDER;
//		intersects->intersections[intersects->intersection_count].material = cyl->material;
//		if (intersects->intersection_count < MAX_INTERSECTS)
//			intersects->intersection_count++;
//		else
//			return (true);
//	}
//	tt[1] = ray->origin.y + t[1] * ray->direction.y;
//	if (tt[1] > cyl->minimum && tt[1] < cyl->maximum)
//	{
//		intersects->intersections[intersects->intersection_count].t = t[1];
//		intersects->intersections[intersects->intersection_count].shape = cyl;
//		intersects->intersections[intersects->intersection_count].type = CYLINDER;
//		intersects->intersections[intersects->intersection_count].material = cyl->material;
//		if (intersects->intersection_count < MAX_INTERSECTS)
//			intersects->intersection_count++;
//	}
//	(void)m;
//	cylinder_end_hit(cyl, ray, intersects);
//	return (true);
//}

t_bool	cylinder_hit(t_minirt *m, t_intersects *intersects, t_ray *ray, t_cylinder *cyl)
{
	float	a;
	float	b;
	float	c;
	float	disc;
	float	t[3];
	float	tt[2];
	t_4dmat	*inverse;
	t_ray	inverse_ray;

	if (!cyl->inverse)
	{
		if (inverse_mat(&cyl->transform, &inverse) == error)
			return (error);
		if (!inverse)
			return (false);
		cyl->inverse = inverse;
		inverse_ray.origin = tuple_mult_fast(cyl->inverse, &ray->origin);
		inverse_ray.direction = tuple_mult_fast(cyl->inverse, &ray->direction);
	}
	a = (inverse_ray.direction.x * inverse_ray.direction.x) + (inverse_ray.direction.z * inverse_ray.direction.z);
	if (is_equal(a, 0))
		return (cylinder_end_hit(cyl, &inverse_ray, intersects));
	b = 2 * (inverse_ray.origin.x * inverse_ray.direction.x) + 2 * (inverse_ray.origin.z * inverse_ray.direction.z);
	c = inverse_ray.origin.x * inverse_ray.origin.x + inverse_ray.origin.z * inverse_ray.origin.z - 1;
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
	tt[0] = inverse_ray.origin.y + t[0] * inverse_ray.direction.y;
	if (cyl->minimum < tt[0] && tt[0] < cyl->maximum)
	{
		if (add_to_intersect(t[0], intersects, CYLINDER, cyl, cyl->material) == false)
			return (true);
	}
	tt[1] = inverse_ray.origin.y + t[1] * inverse_ray.direction.y;
	if (cyl->minimum < tt[1] && tt[1] < cyl->maximum)
		add_to_intersect(t[1], intersects, CYLINDER, cyl, cyl->material);
	(void)m;
	cylinder_end_hit(cyl, &inverse_ray, intersects);
	return (true);
}
