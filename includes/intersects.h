/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:02:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/26 13:50:47 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTS_H
# define INTERSECTS_H

# include "structs.h"

t_inter_comp	precompute_intersect(t_intersects *inter, t_intersection *intersection, t_ray *ray);
//t_intersection	intersect(double t, t_shape_type type);
t_intersection	intersect(double t, t_shape_type type, void *shape, t_mater *material);

t_tuple			normal_pos_plane(t_shape *shape, t_tuple point);

//t_intersects	*intersect_enivornment(t_minirt *minirt, t_ray *ray);
t_intersects	intersect_enivornment(t_minirt *minirt, t_ray *ray);
void			sort_intersects(t_intersects *intersects);
//double			best_hit(t_intersects *intersects);
t_intersection	*best_hit(t_intersects *intersects);
void			print_intersects(t_intersects *inter);

t_tuple			position(t_ray *ray, double t);
t_tuple			normal_pos_cylinder(t_shape *shape, t_tuple pos);

t_cylinder		*create_cylinder(t_tuple orientation);

t_cone			*create_cone();
t_tuple			normal_pos_cone(t_shape *shape, t_tuple pos);

t_bool			add_to_intersect(double t, t_shape *shape_ptr, t_intersects *intersects, t_shape_type type, void *shape);

t_bool			intersect_plane(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index);
t_bool			intersect_cylinder(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index);
t_bool			intersect_cone(t_minirt *m, t_intersects *intersects, t_ray *ray, int shape_index);

t_tuple			normal_at(t_shape *shape, t_tuple point);

#endif