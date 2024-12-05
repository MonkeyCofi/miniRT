/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:38:57 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/05 20:20:40 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	set_inverse_transpose(t_shape *shape, t_4dmat *transform_mat)
{
	t_4dmat	old_inverse;

	old_inverse = shape->inverse_mat;
	if (inverse_mat_test(transform_mat, &shape->inverse_mat) == error)
		return (error);
	shape->inverse_mat = mat4d_mult_fast_static(&shape->inverse_mat, \
	&old_inverse);
	shape->inverse_transpose = transpose(&shape->inverse_mat);
	return (true);
}

t_bool	translate_shape(t_shape *s)
{
	t_4dmat	translation;
	t_4dmat	resultant;

	translation = translation_mat(s->coords.x, s->coords.y, s->coords.z);
	resultant = mat4d_mult_fast_static(&s->transform, &translation);
	s->transform = resultant;
	if (set_inverse_transpose(s, &s->transform) == error)
		return (error);
	return (true);
}

t_4dmat	get_axis_angle(t_tuple *orientation)
{
	t_tuple	default_forward;
	t_tuple	axis;
	double	rotation_angle;

	normalize(orientation);
	default_forward = return_vector(0, 1, 0);
	axis = cross_product(&default_forward, orientation);
	normalize(&axis);
	rotation_angle = acos(dot_product(&default_forward, orientation));
	return (axis_angle(axis, rotation_angle));
}
