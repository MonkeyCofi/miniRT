/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:06:40 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/04 13:16:44 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//# define IS_ROTX_SET(x) (x >> 2) & 1
//# define IS_ROTY_SET(x) (x >> 2) & 1
//# define IS_ROTZ_SET(x) (x >> 2) & 1
//# define IS_SCAL_SET(x) (x >> 1) & 1
//# define IS_TRANS_SET(x) x & 1

t_4dmat	translation_mat(double x, double y, double z)
{
	t_4dmat	translation_mat;
	
	translation_mat = identity();
	translation_mat.m14 = x;
	translation_mat.m24 = y;
	translation_mat.m34 = z;
	return (translation_mat);
}

t_4dmat	scaling_mat(double x, double y, double z)
{
	t_4dmat	scaling_mat;

	scaling_mat = identity();
	scaling_mat.m11 = x;
	scaling_mat.m22 = y;
	scaling_mat.m33 = z;
	scaling_mat.m44 = 1;
	return (scaling_mat);
}

t_4dmat	x_rotation_mat(double angle)
{
	t_4dmat	x_rot;

	ft_bzero(&x_rot, sizeof(t_4dmat));
	x_rot.m11 = 1;
	x_rot.m22 = cos(angle);
	x_rot.m23 = -sin(angle);
	x_rot.m32 = sin(angle);
	x_rot.m33 = cos(angle);
	x_rot.m44 = 1;
	return (x_rot);
}

t_4dmat	y_rotation_mat(double angle)
{
	t_4dmat	y_rot;

	ft_bzero(&y_rot, sizeof(t_4dmat));
	y_rot.m11 = cos(angle);
	y_rot.m13 = sin(angle);
	y_rot.m22 = 1;
	y_rot.m31 = -sin(angle);
	y_rot.m33 = cos(angle);
	y_rot.m44 = 1;
	return (y_rot);
}
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

//t_tuple	scale_ray(t_tuple *point, t_sphere *sphere, double x, double y, double z)
//{
//	t_4dmat	scaling_matrix;
//	t_tuple	*res;
//	t_4dmat	*new_transform;
//	t_tuple	ret;

//	scaling_matrix = scaling_mat(x, y, z);
//	new_transform = mat4d_mult(&scaling_matrix, &sphere->transform);
//	copy_mat(&sphere->transform, new_transform);
//	//free(new_transform);
//	res = tuple_mult(&scaling_matrix, point);
//	if (point->w)
//		set_point_points(&ret, res->x, res->y, res->z);
//	else
//		set_vector_points(&ret, res->x, res->y, res->z);
//	free(res);
//	return (ret);
//}

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

t_ray	transform_ray(t_ray *old_ray, t_trans type, t_tuple transform_coords, t_sphere *sphere)
{
	t_ray	new_ray;
	
	new_ray.origin = return_tuple(0, 0, 0, 1);
	new_ray.direction = return_tuple(0, 0, 0, 0);
	if (type == translate)
	{
		new_ray.origin = translate_ray(&old_ray->origin, transform_coords.x, transform_coords.y, transform_coords.z);
		new_ray.direction = translate_ray(&old_ray->direction, transform_coords.x, transform_coords.y, transform_coords.z);
	}
	else if (type == scale)
	{
		new_ray.origin = scale_ray(&old_ray->origin, transform_coords.x, transform_coords.y, transform_coords.z);
		new_ray.direction = scale_ray(&old_ray->direction, transform_coords.x, transform_coords.y, transform_coords.z);
	}
	(void)sphere;
	return (new_ray);
}

//void	transform_sphere(t_sphere *sphere, t_trans type, char rotation_type, t_tuple transform_coords)
//void	transform_sphere(t_sphere *sphere, t_trans type, t_tuple transform_coords)
//{
//	t_4dmat	trans_matrix;
//	t_4dmat	*res;

//	if (type == translate)
//	{
//		trans_matrix = translation_mat(transform_coords.x, transform_coords.y, transform_coords.z);
//		res = mat4d_mult(&trans_matrix, &sphere->transform);
//		copy_mat(&sphere->transform, res);
//	}
//	else if (type == scale)
//	{
//		trans_matrix = scaling_mat(transform_coords.x, transform_coords.y, transform_coords.z);
//		res = mat4d_mult(&trans_matrix, &sphere->transform);
//		copy_mat(&sphere->transform, res);
//	}
//	inverse_mat(&trans_matrix, &sphere->current_inverse);
//	//else
//	//{
//	//	if (rotation_type == 'x')
//	//		trans_matrix = x_rotation_mat
//	//}
//}

t_4dmat	get_axis_angle(t_tuple *orientation)
{
	t_tuple	default_forward;
	t_tuple	axis;
	double	rotation_angle;

	normalize(orientation);
	default_forward = return_vector(0, 1, 0);
	axis = cross_product(&default_forward, orientation);
	normalize(&axis);
	printf("axis: ");
	print_tuple_points(&axis);
	rotation_angle = acos(dot_product(&default_forward, orientation));
	return (axis_angle(axis, rotation_angle));
}

t_bool	set_inverse_transpose(t_shape *shape, t_4dmat *transform_mat)
{
	t_4dmat	*old_inverse;

	old_inverse = shape->inverse_mat;
	if (inverse_mat(transform_mat, &shape->inverse_mat) == error)
		return (error);
	shape->inverse_mat = mat4d_mult_fast(shape->inverse_mat, old_inverse);
	if (shape->inverse_transpose)
	{
		free(shape->inverse_transpose);
		shape->inverse_transpose = NULL;
	}
	shape->inverse_transpose = transpose(shape->inverse_mat);
	if (!shape->inverse_transpose)
		return (error);
	free(old_inverse);
	return (true);
}

t_bool	transform_shape(t_minirt *m, int index, t_trans type, double angle, t_tuple *transform_coords)
{
	t_bool	inverse_res;
	t_4dmat	translation;
	t_4dmat	scaling;
	t_4dmat	rotation;
	t_4dmat	resultant;

	scaling = identity();
	rotation = identity();
	translation = identity();
	if (type == none)
	{
		inverse_res = inverse_mat(&m->shapes[index]->transform, &m->shapes[index]->inverse_mat);
		return (true);
	}
	(void)inverse_res;
	if (type == translate)
		translation = translation_mat(transform_coords->x, transform_coords->y,  transform_coords->z);
	else if (type == scale)
		scaling = scaling_mat(transform_coords->x, transform_coords->y,  transform_coords->z);
	else if (type == rotate_x)
		rotation = x_rotation_mat(angle);
	else if (type == rotate_y)
		rotation = y_rotation_mat(angle);
	else if (type == rotate_z)
		rotation = z_rotation_mat(angle);
	resultant = mat4d_mult_fast_static(&translation, &scaling);
	resultant = mat4d_mult_fast_static(&resultant, &rotation);
	// resultant = mat4d_mult_fast_static(&scaling, &rotation);
	// resultant = mat4d_mult_fast_static(&resultant, &translation);
	m->shapes[index]->transform = mat4d_mult_fast_static(&resultant,&m->shapes[index]->transform);
	if (set_inverse_transpose(m->shapes[index], &m->shapes[index]->transform) == error)
		return (error);
	return (true);
}

void	get_transform_params_rotations(double x, double y, double z, t_transform *trans_params)
{
	trans_params->rotation_x = x;
	trans_params->rotation_y = y;
	trans_params->rotation_z = z;
}

void	get_transform_params(t_tuple translate, t_tuple scaling, t_transform *trans_params)
{
	trans_params->translation = translate;
	trans_params->scaling = scaling;
}

//void	get_trans_order(t_transform *trans_params, )
//{

//}

//t_bool	transform_shape_new(t_shape *shape, t_transform *transform_params)
//{
//	int	i;

//	i = -1;
//	while (++i < 5)
//	{
//		if (transform_params->transformations[i] == none)
//		{
//			printf("none\n");
//			continue ;
//		}
//		else if (transform_params->transformations[i] == scale)
//		{
//			printf("%d scale", i);
//			shape->scaling_mat = scaling_mat(transform_params->scaling.x, transform_params->scaling.y, transform_params->scaling.z);
//			shape->transform = mat4d_mult_fast_static(&shape->transform, &shape->scaling_mat);
//		}
//		else if (transform_params->transformations[i] == translate)
//		{
//			printf("%i translate\n", i);
//			shape->translation_mat = translation_mat(transform_params->translation.x, transform_params->translation.y, transform_params->translation.z);
//			shape->transform = mat4d_mult_fast_static(&shape->transform, &shape->translation_mat);
//		}
//		else if (transform_params->transformations[i] == rotate_x)
//		{
//			printf("%d rotate x\n", i);
//			shape->rotation_mat = x_rotation_mat(transform_params->rotation_x);
//			shape->transform = mat4d_mult_fast_static(&shape->transform, &shape->rotation_mat);
//		}
//		else if (transform_params->transformations[i] == rotate_y)
//		{
//			printf("%d rotate y\n", i);
//			shape->rotation_mat = y_rotation_mat(transform_params->rotation_y);
//			shape->transform = mat4d_mult_fast_static(&shape->transform, &shape->rotation_mat);
//		}
//		else if (transform_params->transformations[i] == rotate_z)
//		{
//			printf("%d rotate z\n", i);
//			shape->rotation_mat = z_rotation_mat(transform_params->rotation_z);
//			shape->transform = mat4d_mult_fast_static(&shape->transform, &shape->rotation_mat);
//		}
//	}
//	if (set_inverse_transpose(shape, &shape->transform) == error)
//		return (error);
//	return (true);
//}
