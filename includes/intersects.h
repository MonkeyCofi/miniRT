/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:02:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/09 19:36:30 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTS_H
# define INTERSECTS_H

# include "structs.h"

//t_inter_comp	*precompute_intersect(t_intersects *inter, t_intersection *intersection, t_ray *ray, t_sphere *sphere);
//t_intersection	intersect(float t, t_shape_type type);
t_intersection	intersect(float t, t_shape_type type, void *shape, t_ray *ray, t_trans trans_type, t_tuple trans_coords);
t_intersects	*intersect_enivornment(t_mlx *mlx, t_minirt *minirt, t_ray *ray, t_sphere *sphere);
void			sort_intersects(t_intersects *intersects);
float			best_hit(t_intersects *intersects);
void			print_intersects(t_intersects *inter);

t_tuple			*normal_pos(t_sphere *sphere, t_tuple pos);
t_tuple			position(t_ray *ray, float t);

#endif