/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:06:58 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 15:22:53 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cone	*create_cone(t_minirt *m)
{
	t_cone	*cone;

	cone = calloc_and_check(sizeof(t_cone), 1, m, CON_ERR);
	cone->point = return_tuple(0, 0, 0, POINT);
	cone->material = create_default_material();
	cone->type = CONE;
	cone->minimum = -INFINITY;
	cone->maximum = INFINITY;
	cone->is_closed = true;
	return (cone);
}

static t_bool	at_cap(t_ray *ray, double t, t_cone *cone, double y)
{
	double	x;
	double	z;
	double	radius;

	x = ray->origin.x + t * ray->direction.x;
	z = ray->origin.z + t * ray->direction.z;
	radius = (cone->maximum - y) / (cone->maximum - cone->minimum);
	return ((x * x) + (z * z) <= (radius * radius));
}

t_tuple	normal_pos_cone(t_shape *shape, t_tuple pos)
{
	t_cone		*cone;
	double		distance;
	double		y;

	cone = shape->shape;
	distance = (pos.x * pos.x) + (pos.z * pos.z);
	if (distance < 1 && (pos.y > cone->maximum - EPSILON || is_equal(pos.y, \
	cone->maximum - EPSILON)))
		return (return_vector(0, 1, 0));
	else if (distance < 1 && (pos.y < cone->minimum + EPSILON || is_equal(\
	pos.y, cone->minimum + EPSILON)))
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
	if (t > cone->minimum && at_cap(ray, t, cone, cone->minimum))
	{
		if (add_to_intersect(t, shape_ptr, intersects) == false)
			return (true);
	}
	t = (cone->maximum - ray->origin.y) / ray->direction.y;
	if (at_cap(ray, t, cone, cone->maximum))
		add_to_intersect(t, shape_ptr, intersects);
	return (true);
}

void	init_cone(t_minirt *m, int *i)
{
	t_cone	*cone;
	t_shape	*parsed;
	t_4dmat	rot;

	cone = create_cone(m);
	parsed = m->shapes[*i];
	cone->minimum = -(m->shapes[*i]->h / 2);
	cone->maximum = (m->shapes[*i]->h / 2);
	m->shapes[*i] = create_shape(m, CONE, cone);
	m->shapes[*i]->material = parsed->material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(parsed->material->pattern.color_one, \
		parsed->material->pattern.color_two, 10, &parsed->material->pattern);
	m->shapes[*i]->transform = identity();
	m->shapes[*i]->coords = parsed->coords;
	transform_shape(m->shapes[*i], translate, 0);
	rot = get_axis_angle(&parsed->orientation);
	m->shapes[*i]->transform = mat4d_mult_fast_static(\
	&m->shapes[*i]->transform, &rot);
	set_inverse_transpose(m->shapes[*i], &m->shapes[*i]->transform);
	*i += 1;
}
