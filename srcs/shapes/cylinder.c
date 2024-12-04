/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:49:13 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 10:57:20 by ahaarij          ###   ########.fr       */
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



void	init_cylinder(t_minirt *m, int *i)
{
	t_cylinder	*cylinder;
	t_thing		s;
	t_tuple		orientation;
	t_mater		*material;
	t_4dmat		rot;

	cylinder = create_cylinder(m);
	s.i = *i;
	s.coords = m->shapes[*i]->coords;
	orientation = m->shapes[*i]->orientation;
	material = m->shapes[*i]->material;
	cylinder->maximum = m->shapes[*i]->h;
	cylinder->radius = m->shapes[*i]->r;
	free(m->shapes[*i]);
	m->shapes[*i] = create_shape(m, CYLINDER, cylinder);
	m->shapes[*i]->r = cylinder->radius;
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
