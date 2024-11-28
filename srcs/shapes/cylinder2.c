/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:29:27 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/28 10:23:27 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	bottom(t_minirt *m, t_intersects *intersects, \
t_ray *ray, t_norm_cyl *s)
{
	int		shape_index;
	double	t_bottom;
	double	x;
	double	z;

	shape_index = s->shape_index;
	if (ray->direction.y != 0 && s->cyl->is_closed)
	{
		t_bottom = (s->cyl->minimum - ray->origin.y) / ray->direction.y;
		if (t_bottom >= 0)
		{
			x = ray->origin.x + t_bottom * ray->direction.x;
			z = ray->origin.z + t_bottom * ray->direction.z;
			if (x * x + z * z <= s->cyl->radius)
				add_to_intersect(t_bottom, m->shapes[shape_index], \
				intersects, CYLINDER, s->cyl);
		}
	}
}

void	top(t_minirt *m, t_intersects *intersects, t_ray *ray, t_norm_cyl *s)
{
	int		shape_index;
	double	t_top;
	double	x;
	double	z;

	shape_index = s->shape_index;
	if (ray->direction.y != 0 && s->cyl->is_closed)
	{
		t_top = (s->cyl->maximum - ray->origin.y) / ray->direction.y;
		if (t_top >= 0)
		{
			x = ray->origin.x + t_top * ray->direction.x;
			z = ray->origin.z + t_top * ray->direction.z;
			if (x * x + z * z <= s->cyl->radius)
			{
				add_to_intersect(t_top, m->shapes[shape_index], \
				intersects, CYLINDER, s->cyl);
			}
		}
	}
}

void	body(t_minirt *m, t_intersects *intersects, t_ray *ray, t_norm_cyl *s)
{
	int	i;
	int	shape_index;

	i = 0;
	shape_index = s->shape_index;
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
			if (s->cyl->minimum < s->y[i] && s->y[i] < s->cyl->maximum)
			{
				add_to_intersect(s->t[i], m->shapes[shape_index], \
				intersects, CYLINDER, s->cyl);
			}
			i++;
		}
	}
}

t_bool	intersect_cylinder(t_minirt *m, t_intersects *intersects, t_ray *ray, \
int shape_index)
{
	t_norm_cyl	s;

	s.cyl = m->shapes[shape_index]->shape;
	s.shape_index = shape_index;
	s.a = (ray->direction.x * ray->direction.x) + (ray->direction.z * \
													ray->direction.z);
	if (s.a < EPSILON)
		return (cylinder_end_hit(s.cyl, m->shapes[shape_index], \
		ray, intersects));
	s.b = 2 * ray->origin.x * ray->direction.x + 2 * ray->origin.z * \
	ray->direction.z;
	s.c = ray->origin.x * ray->origin.x + ray->origin.z * ray->origin.z \
	- s.cyl->radius;
	s.disc = (s.b * s.b) - (4 * s.a * s.c);
	body(m, intersects, ray, &s);
	bottom(m, intersects, ray, &s);
	top(m, intersects, ray, &s);
	return (true);
}
