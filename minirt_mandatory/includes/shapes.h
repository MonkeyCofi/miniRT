/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:57:12 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/05 20:20:51 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "structs.h"

t_shape		*create_shape(t_minirt *m, t_shape_type type, void *shape_ptr);

t_cylinder	*create_cylinder(t_minirt *m);

t_plane		*create_plane(t_minirt *m);

void		assign_normal_intersect_func(t_shape *shape, t_shape_type type);

t_bool		intersect_plane(t_intersects *intersects, t_ray *ray, \
			t_shape *shape);

t_bool		intersect_cylinder(t_intersects *intersects, t_ray *ray, \
								t_shape *shape);

t_bool		intersect_cone(t_intersects *intersects, t_ray *ray, \
							t_shape *shape);

t_bool		cylinder_end_hit(t_cylinder *cylinder, t_shape *shape_ptr, \
							t_ray *ray, t_intersects *intersects);

t_tuple		normal_pos_plane(t_shape *shape, t_tuple point);

t_tuple		normal_pos_cylinder(t_shape *shape, t_tuple pos);

t_tuple		normal_pos_cone(t_shape *shape, t_tuple pos);

t_tuple		normal_at(t_shape *shape, t_tuple point);

#endif