/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cone.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:53:36 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/04 20:48:10 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_cone(t_minirt *m, int *i)
{
	t_cone	*cone;
	t_tuple	orientation;
	t_thing	s;
	t_mater	*material;
	t_4dmat	rot;

	cone = create_cone(m);
	s.i = *i;
	material = m->shapes[*i]->material;
	s.coords = m->shapes[*i]->coords;
	orientation = m->shapes[*i]->orientation;
	cone->minimum = -(m->shapes[*i]->h / 2);
	cone->maximum = (m->shapes[*i]->h / 2);
	m->shapes[*i] = create_shape(m, CONE, cone);
	m->shapes[*i]->material = material;
	if (m->shapes[*i]->material->is_patterned == true)
		create_pattern(material->pattern.color_one, m->shapes \
	[*i]->material->pattern.color_two, 10, &m->shapes[*i]->material->pattern);
	m->shapes[*i]->transform = identity();
	//transform_shape(m, &s, translate, 0);
	translate_shape(m->shapes[*i]);
	rot = get_axis_angle(&orientation);
	m->shapes[*i]->transform = mat4d_mult_fast_static(\
	&m->shapes[*i]->transform, &rot);
	set_inverse_transpose(m->shapes[*i], &m->shapes[*i]->transform);
	*i += 1;
}
