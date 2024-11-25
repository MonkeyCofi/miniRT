/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:53:36 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/25 18:59:28 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cone(t_minirt *m, int *i)
{
	t_cone	*cone;
	t_tuple	coords;
	t_tuple	orientation;
	t_mater	*material;
	t_4dmat	rot;

	cone = create_cone(m);
	material = m->shapes[*i]->material;
	coords = m->shapes[*i]->coords;
	orientation = m->shapes[*i]->orientation;
	cone->minimum = -m->shapes[*i]->h;
	cone->maximum = m->shapes[*i]->h;
	m->shapes[*i] = create_shape(CONE, cone);
	m->shapes[*i]->material = material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(material->pattern.color_one,
			m->shapes[*i]->material->pattern.color_two,
			10, &m->shapes[*i]->material->pattern);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, translate, 0, &coords);
	rot = get_axis_angle(&orientation);
	m->shapes[*i]->transform = mat4d_mult_fast_static(\
	&m->shapes[*i]->transform, &rot);
	set_inverse_transpose(m->shapes[*i], &m->shapes[*i]->transform);
	*i += 1;
}
