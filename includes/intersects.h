/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 21:02:46 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 19:34:16 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTS_H
# define INTERSECTS_H

# include "structs.h"

t_inter_comp	precompute_intersect(t_minirt *minirt, t_intersects *inter, \
									t_intersection *intersection, t_ray *ray);

t_intersection	intersect(double t, t_shape_type type, void *shape, \
				t_mater *material);

t_intersects	intersect_enivornment(t_minirt *minirt, t_ray *ray);

t_bool			add_to_intersect(double t, t_shape *shape, \
								t_intersects *intersects);

void			sort_intersects(t_intersects *intersects);

t_intersection	*best_hit(t_intersects *intersects);

t_tuple			position(t_ray *ray, double t);

#endif