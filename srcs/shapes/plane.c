/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 20:40:35 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/02 18:52:29 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*create_plane(t_minirt *m)
{
	t_plane	*plane;

	plane = calloc_and_check(sizeof(t_plane), 1, m, PL_ERR);
	return (plane);
}

t_bool	intersect_plane(t_intersects *intersects, t_ray *ray, t_shape *shape)
{
	if (fabs(ray->direction.y) < EPSILON)
		return (false);
	add_to_intersect(-ray->origin.y / ray->direction.y, shape, intersects);
	return (true);
}

t_tuple	normal_pos_plane(t_shape *object, t_tuple point)
{
	(void)object;
	(void)point;
	return (return_vector(0, 1, 0));
}

void	init_plane(t_minirt *m, int *i)
{
	t_4dmat	rot;
	t_plane	*plane;
	t_thing	s;
	t_mater	*material;
	t_tuple	orientation;

	s.i = *i;
	s.coords = m->shapes[*i]->coords;
	plane = create_plane(m);
	material = m->shapes[*i]->material;
	orientation = m->shapes[*i]->orientation;
	free(m->shapes[*i]);
	m->shapes[*i] = create_shape(m, PLANE, plane);
	m->shapes[*i]->material = material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(material->pattern.color_one,
			m->shapes[*i]->material->pattern.color_two,
			10, &m->shapes[*i]->material->pattern);
	transform_shape(m, &s, translate, 0);
	rot = get_axis_angle(&orientation);
	m->shapes[*i]->transform = mat4d_mult_fast_static(\
						&m->shapes[*i]->transform, &rot);
	set_inverse_transpose(m->shapes[*i], &m->shapes[*i]->transform);
	*i += 1;
}
