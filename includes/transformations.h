/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:13:25 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 18:50:13 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "structs.h"

//typedef struct	s_transform
//{
//	t_4dmat	*transformations;
//	t_trans	*types;
//	t_tuple	*points;
//	double	rot_angle_x;
//	double	rot_angle_y;
//	double	rot_angle_z;
//	int		trans_count;
//}	t_transform;

t_4dmat	translation_mat(double x, double y, double z);

t_4dmat	scaling_mat(double x, double y, double z);

t_4dmat	x_rotation_mat(double angle);

t_4dmat	y_rotation_mat(double angle);

t_4dmat	z_rotation_mat(double angle);

t_tuple	translate_ray(t_tuple *point, double x, double y, double z);

t_tuple	scale_ray(t_tuple *point, double x, double y, double z);

t_ray	transform_ray(t_ray *old_ray, t_trans type, t_tuple transform_coords, \
															t_sphere *sphere);

void	transform_sphere(t_sphere *sphere, t_trans type, \
										t_tuple transform_coords);

t_tuple	chain_transforms(t_transform *trans, t_tuple *point);

t_bool	transform_shape(t_shape *s, t_trans type, double angle);

t_bool	translate_shape(t_shape *s);

//t_bool	transform_shape_new(t_shape *shape, t_transform *transform_params);

void	get_transform_params_rotations(double x, double y, double z, \
												t_transform *trans_params);

void	get_transform_params(t_tuple translate, t_tuple scaling, \
												t_transform *trans_params);

t_4dmat	get_axis_angle(t_tuple *orientation);

t_bool	set_inverse_transpose(t_shape *shape, t_4dmat *transform_mat);

#endif