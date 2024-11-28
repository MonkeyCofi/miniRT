/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:39:23 by ahaarij           #+#    #+#             */
/*   Updated: 2024/11/26 10:31:30 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_4dmat	z_rotation_mat(double angle)
{
	t_4dmat	z_rot;

	ft_bzero(&z_rot, sizeof(t_4dmat));
	z_rot.m33 = 1;
	z_rot.m11 = cos(angle);
	z_rot.m12 = -sin(angle);
	z_rot.m21 = sin(angle);
	z_rot.m22 = cos(angle);
	z_rot.m44 = 1;
	return (z_rot);
}

t_tuple	scale_ray(t_tuple *point, double x, double y, double z)
{
	t_4dmat	scaling_matrix;
	t_tuple	*res;
	t_tuple	ret;

	scaling_matrix = scaling_mat(x, y, z);
	res = tuple_mult(&scaling_matrix, point);
	ret = return_tuple(res->x, res->y, res->z, res->w);
	return (ret);
}

t_tuple	translate_ray(t_tuple *point, double x, double y, double z)
{
	t_4dmat	translation_matrix;
	t_tuple	*resultant;
	t_tuple	ret;

	translation_matrix = translation_mat(x, y, z);
	resultant = tuple_mult(&translation_matrix, point);
	set_point_points(&ret, resultant->x, resultant->y, resultant->z);
	free(resultant);
	return (ret);
}

t_ray	transform_ray(t_ray *old_ray, t_trans type, t_tuple transform_coords, \
t_sphere *sphere)
{
	t_ray	new_ray;

	new_ray.origin = return_tuple(0, 0, 0, 1);
	new_ray.direction = return_tuple(0, 0, 0, 0);
	if (type == translate)
	{
		new_ray.origin = translate_ray(&old_ray->origin, \
		transform_coords.x, transform_coords.y, transform_coords.z);
		new_ray.direction = translate_ray(&old_ray->direction, \
		transform_coords.x, transform_coords.y, transform_coords.z);
	}
	else if (type == scale)
	{
		new_ray.origin = scale_ray(&old_ray->origin, \
		transform_coords.x, transform_coords.y, transform_coords.z);
		new_ray.direction = scale_ray(&old_ray->direction, \
		transform_coords.x, transform_coords.y, transform_coords.z);
	}
	(void)sphere;
	return (new_ray);
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
