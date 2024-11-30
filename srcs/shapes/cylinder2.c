/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:29:27 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/30 11:18:16 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bottom(t_intersects *intersects, t_ray *ray, t_disc *s, t_shape *shape)
{
	t_cylinder	*cyl;
	double		t_bottom;
	double		x;
	double		z;

	cyl = s->shape;
	if (ray->direction.y != 0 && cyl->is_closed)
	{
		t_bottom = (cyl->minimum - ray->origin.y) / ray->direction.y;
		if (t_bottom >= 0)
		{
			x = ray->origin.x + t_bottom * ray->direction.x;
			z = ray->origin.z + t_bottom * ray->direction.z;
			if (x * x + z * z <= cyl->radius)
				add_to_intersect(t_bottom, shape, intersects);
		}
	}
}

void	top(t_intersects *intersects, t_ray *ray, t_disc *s, t_shape *shape)
{
	t_cylinder	*cyl;
	double		t_top;
	double		x;
	double		z;

	cyl = s->shape;
	if (ray->direction.y != 0 && cyl->is_closed)
	{
		t_top = (cyl->maximum - ray->origin.y) / ray->direction.y;
		if (t_top >= 0)
		{
			x = ray->origin.x + t_top * ray->direction.x;
			z = ray->origin.z + t_top * ray->direction.z;
			if (x * x + z * z <= cyl->radius)
				add_to_intersect(t_top, shape, intersects);
		}
	}
}

void	body(t_intersects *intersects, t_ray *ray, t_disc *s, t_shape *shape)
{
	int			i;
	t_cylinder	*cyl;

	i = 0;
	cyl = s->shape;
	if (s->disc >= 0)
	{
		s->a *= 2;
		s->b = -s->b;
		s->disc = sqrt(s->disc);
		s->t[0] = (s->b - s->disc) / s->a;
		s->t[1] = (s->b + s->disc) / s->a;
		while (i < 2)
		{
			s->y[i] = ray->origin.y + s->t[i] * ray->direction.y;
			if (cyl->minimum < s->y[i] && s->y[i] < cyl->maximum)
				add_to_intersect(s->t[i], shape, intersects);
			i++;
		}
	}
}

t_bool	intersect_cylinder(t_intersects *intersects, t_ray *ray, t_shape *shape)
{
	t_disc		s;
	t_cylinder	*cyl;

	s.shape = shape->shape;
	cyl = shape->shape;
	s.a = (ray->direction.x * ray->direction.x) + (ray->direction.z * \
													ray->direction.z);
	if (s.a < EPSILON)
		return (cylinder_end_hit(cyl, shape, ray, intersects));
	s.b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * \
	ray->direction.z;
	s.c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z \
		- cyl->radius;
	s.disc = (s.b * s.b) - (4 * s.a * s.c);
	body(intersects, ray, &s, shape);
	bottom(intersects, ray, &s, shape);
	top(intersects, ray, &s, shape);
	return (true);
}
