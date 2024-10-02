/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 21:13:25 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/02 20:10:28 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATIONS_H
# define TRANSFORMATIONS_H

# include "structs.h"

t_4dmat	translation_mat(float x, float y, float z);
t_4dmat	scaling_mat(float x, float y, float z);
t_4dmat	x_rotation_mat(float angle);
t_4dmat	y_rotation_mat(float angle);
t_4dmat	z_rotation_mat(float angle);

t_tuple	translate_ray(t_tuple *point, float x, float y, float z);
t_tuple	scale_ray(t_tuple *point, t_sphere *sphere, float x, float y, float z);

#endif