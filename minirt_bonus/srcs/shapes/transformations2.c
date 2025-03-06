/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:38:57 by ahaarij           #+#    #+#             */
/*   Updated: 2024/12/10 19:01:56 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	set_inverse_transpose(t_shape *shape, t_4dmat *transform_mat)
{
	t_4dmat	old_inverse;

	old_inverse = shape->inverse_mat;
	if (inverse_mat(transform_mat, &shape->inverse_mat) == error)
		return (error);
	shape->inverse_mat = mat4d_mult(&shape->inverse_mat, \
	&old_inverse);
	shape->inverse_transpose = transpose(&shape->inverse_mat);
	return (true);
}

t_bool	check_rotation(t_4dmat *rotation, double angle, t_trans type)
{
	t_bool	changed;

	changed = false;
	if (type == rotate_x)
	{
		*rotation = x_rotation_mat(angle);
		changed = true;
	}
	else if (type == rotate_y)
	{
		*rotation = y_rotation_mat(angle);
		changed = true;
	}
	else if (type == rotate_z)
	{
		*rotation = z_rotation_mat(angle);
		changed = true;
	}
	return (changed);
}

t_bool	transform_shape(t_shape *s, t_trans type, double angle)
{
	t_4dmat	translation;
	t_4dmat	scaling;
	t_4dmat	rotation;
	t_4dmat	resultant;

	scaling = identity();
	rotation = identity();
	translation = identity();
	if (type == none)
		return (inverse_mat(&s->transform, \
		&s->inverse_mat));
	if (type == translate)
		translation = translation_mat(s->coords.x, s->coords.y, s->coords.z);
	else if (type == scale)
		scaling = scaling_mat(s->coords.x, s->coords.y, s->coords.z);
	else
		check_rotation(&rotation, angle, type);
	resultant = mat4d_mult(&translation, &scaling);
	resultant = mat4d_mult(&resultant, &rotation);
	s->transform = mat4d_mult(\
	&s->transform, &resultant);
	if (set_inverse_transpose(s, &s->transform) == error)
		return (error);
	return (true);
}

t_bool	translate_shape(t_shape *s)
{
	t_4dmat	translation;
	t_4dmat	resultant;

	translation = translation_mat(s->coords.x, s->coords.y, s->coords.z);
	resultant = mat4d_mult(&s->transform, &translation);
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
