/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:38:57 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/28 00:12:41 by ahaarij          ###   ########.fr       */
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

t_bool	check_rotation(t_4dmat rotation, double angle, t_trans type)
{
	t_bool	changed;

	changed = false;
	if (type == rotate_x)
	{
		rotation = x_rotation_mat(angle);
		changed = true;
	}
	else if (type == rotate_y)
	{
		rotation = y_rotation_mat(angle);
		changed = true;
	}
	else if (type == rotate_z)
	{
		rotation = z_rotation_mat(angle);
		changed = true;
	}
	return (changed);
}

t_bool	transform_shape(t_minirt *m, t_thing *s, t_trans type, double angle)
{
	t_4dmat	translation;
	t_4dmat	scaling;
	t_4dmat	rotation;
	t_4dmat	resultant;

	scaling = identity();
	rotation = identity();
	translation = identity();
	if (type == none)
		return (inverse_mat_test(&m->shapes[s->i]->transform, \
		&m->shapes[s->i]->inverse_mat));
	if (type == translate)
		translation = translation_mat(s->coords.x, s->coords.y, s->coords.z);
	else if (type == scale)
		scaling = scaling_mat(s->coords.x, s->coords.y, s->coords.z);
	else
		check_rotation(rotation, angle, type);
	resultant = mat4d_mult_fast_static(&translation, &scaling);
	resultant = mat4d_mult_fast_static(&resultant, &rotation);
	m->shapes[s->i]->transform = mat4d_mult_fast_static(\
	&m->shapes[s->i]->transform, &resultant);
	if (set_inverse_transpose(m->shapes[s->i], \
	&m->shapes[s->i]->transform) == error)
		return (error);
	return (true);
}

void	get_transform_params_rotations(double x, double y, \
double z, t_transform *trans_params)
{
	trans_params->rotation_x = x;
	trans_params->rotation_y = y;
	trans_params->rotation_z = z;
}

void	get_transform_params(t_tuple translate, t_tuple scaling, \
t_transform *trans_params)
{
	trans_params->translation = translate;
	trans_params->scaling = scaling;
}
