/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:13:25 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/19 20:35:50 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "structs.h"

typedef struct	s_tranform
{
	t_4dmat	*transformations;
	t_trans	*types;
	t_tuple	*points;
	float	rot_angle_x;
	float	rot_angle_y;
	float	rot_angle_z;
	int		trans_count;
}	t_transform;

t_4dmat	translation_mat(float x, float y, float z);
t_4dmat	scaling_mat(float x, float y, float z);
t_4dmat	x_rotation_mat(float angle);
t_4dmat	y_rotation_mat(float angle);
t_4dmat	z_rotation_mat(float angle);

t_tuple	translate_ray(t_tuple *point, float x, float y, float z);
//t_tuple	scale_ray(t_tuple *point, t_sphere *sphere, float x, float y, float z);
t_tuple	scale_ray(t_tuple *point, float x, float y, float z);

t_ray	transform_ray(t_ray *old_ray, t_trans type, t_tuple transform_coords, t_sphere *sphere);
void	transform_sphere(t_sphere *sphere, t_trans type, t_tuple transform_coords);
t_tuple	chain_transforms(t_transform *trans, t_tuple *point);

t_bool	transform_shape(t_minirt *m, int index, t_trans type, float angle, t_tuple *transform_coords);

#endif