/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:13:25 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 18:50:16 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "structs.h"

t_4dmat	translation_mat(double x, double y, double z);

t_4dmat	scaling_mat(double x, double y, double z);

t_4dmat	x_rotation_mat(double angle);

t_4dmat	y_rotation_mat(double angle);

t_4dmat	z_rotation_mat(double angle);

t_bool	translate_shape(t_shape *s);

t_4dmat	get_axis_angle(t_tuple *orientation);

t_bool	set_inverse_transpose(t_shape *shape, t_4dmat *transform_mat);

#endif