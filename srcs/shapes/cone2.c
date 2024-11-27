/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:04:16 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/27 11:32:32 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	pt2(t_norm_cone *s, t_minirt *m, t_intersects *intersects, t_ray *ray)
{
	int	shape_index;

	shape_index = s->shape_index;
	s->disc = (s->b * s->b) - 4 * s->a * s->c;
	if (s->disc < 0)
		return (false);
	s->a *= 2;
	s->b *= -1;
	s->t[0] = (s->b - sqrt(s->disc)) / (s->a);
	s->t[1] = (s->b + sqrt(s->disc)) / (s->a);
	s->y[0] = ray->origin.y + s->t[0] * ray->direction.y;
	if (s->y[0] > s->cone->minimum && s->y[0] < s->cone->maximum)
	{
		if (add_to_intersect(s->t[0], m->shapes[shape_index], intersects, \
		CONE, s->cone) == false)
			return (true);
	}
	s->y[1] = ray->origin.y + s->t[1] * ray->direction.y;
	if (s->y[1] > s->cone->minimum && s->y[1] < s->cone->maximum)
		add_to_intersect(s->t[1], m->shapes[shape_index], intersects, \
		CONE, s->cone);
	return (true);
}

t_bool	intersect_cone(t_minirt *m, t_intersects *intersects, t_ray *ray, \
int shape_index)
{
	t_norm_cone	s;

	s.shape_index = shape_index;
	s.cone = m->shapes[shape_index]->shape;
	s.a = (ray->direction.x * ray->direction.x) - (ray->direction.y * \
	ray->direction.y) + (ray->direction.z * ray->direction.z);
	s.b = (2 * ray->origin.x * ray->direction.x) - (2 * ray->origin.y * \
	ray->direction.y) + (2 * ray->origin.z * ray->direction.z);
	s.c = (ray->origin.x * ray->origin.x) - (ray->origin.y * ray->origin.y) + \
	(ray->origin.z * ray->origin.z);
	if (is_equal(s.a, 0))
	{
		if (is_equal(s.b, 0))
			return (false);
		if (add_to_intersect(-s.c / (2 * s.b), m->shapes[shape_index], \
		intersects, CONE, s.cone) == false)
			return (true);
	}
	if (pt2(&s, m, intersects, ray) == false)
		return (false);
	return (true);
}
