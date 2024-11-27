/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:57:12 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/27 09:36:34 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "structs.h"

t_shape	*create_shape(t_shape_type type, void *shape_ptr);

void	assign_normal_intersect_func(t_shape *shape, t_shape_type type);

t_plane	*create_plane(t_minirt *m);

t_bool	intersect_plane(t_minirt *m, t_intersects *intersects, \
										t_ray *ray, int shape_index);

t_tuple	normal_pos_plane(t_shape *object, t_tuple point);

#endif