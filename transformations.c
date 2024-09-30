/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:06:40 by pipolint          #+#    #+#             */
/*   Updated: 2024/09/30 12:31:36 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_4dmat	translation_mat(float x, float y, float z)
{
	t_4dmat	translation_mat;
	
	translation_mat = identity();
	translation_mat.m14 = x;
	translation_mat.m24 = y;
	translation_mat.m34 = z;
	return (translation_mat);
}

t_4dmat	scaling_mat(float x, float y, float z)
{
	t_4dmat	scaling_mat;

	scaling_mat = identity();
	scaling_mat.m11 = x;
	scaling_mat.m22 = y;
	scaling_mat.m33 = z;
	return (scaling_mat);
}

t_4dmat	x_rotation_mat(float angle)
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

t_4dmat	y_rotation_mat(float angle)
{
	t_4dmat	y_rot;

	ft_bzero(&y_rot, sizeof(t_4dmat));
	y_rot.m22 = 1;
	y_rot.m11 = cos(angle);
	y_rot.m13 = sin(angle);
	y_rot.m31 = -sin(angle);
	y_rot.m33 = cos(angle);
	y_rot.m44 = 1;
	return (y_rot);
}
t_4dmat	z_rotation_mat(float angle)
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

t_tuple	scale(t_tuple *point, float x, float y, float z)
{
	t_4dmat	scaling_matrix;
	t_tuple	*res;
	t_tuple	ret;

	scaling_matrix = scaling_mat(x, y, z);
	res = tuple_mult(&scaling_matrix, point);
	if (point->w)
		set_point_points(&ret, res->x, res->y, res->z);
	else
		set_vector_points(&ret, res->x, res->y, res->z);
	free(res);
	return (ret);
}

t_tuple	translate(t_tuple *point, float x, float y, float z)
{
	t_4dmat	translation_matrix;
	t_tuple	*resultant;
	t_tuple	ret;

	translation_matrix = translation_mat(x, y, z);
	resultant = tuple_mult(&translation_matrix, point);
	set_point_points(&ret, resultant->x, resultant->y, resultant->z);
	free(resultant);
	return (ret);
	//t_tuple	ret;
	//t_4dmat	id;
	//t_tuple	*res;

	//id = identity();
	//id.m14 = x;
	//id.m24 = y;
	//id.m34 = z;
	//res = tuple_mult(&id, point);
	//set_point_points(&ret, res->x, res->y, res->z);
	//free(res);
	//return (ret);
}