/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:19:36 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/29 21:24:50 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

uint32_t	get_ray_color(t_tuple	*color)
{
	uint32_t		res;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	set_min_max(color);
	r = color->r * 255;
	g = color->g * 255;
	b = color->b * 255;
	a = color->a;
	res = a << 24 | r << 16 | g << 8 | b;
	return (res);
}

uint32_t	get_ray_coloraarij(t_tuple	*color)
{
	uint32_t		res;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	set_min_max(color);
	r = color->r * 255;
	g = color->g * 255;
	b = color->b * 255;
	a = color->a;
	res = a << 24 | r << 16 | g << 8 | b;
	return (res);
}

static inline t_bool	is_in_shadow(t_minirt *minirt, t_tuple point, \
int light_index)
{
	t_intersection	*hit;
	t_intersects	intersect;
	t_tuple			direction;
	t_ray			ray;
	t_norm_color	s;

	s.new_point = (t_tuple){0};
	s.new_point = subtract_tuples(&point, \
	&minirt->lights[light_index]->position);
	direction = return_tuple(s.new_point.x, \
	s.new_point.y, s.new_point.z, VECTOR);
	normalize(&direction);
	s.distance = magnitude(&direction);
	ray = create_ray_static(point, direction);
	intersect = intersect_enivornment(minirt, &ray);
	hit = best_hit(&intersect);
	if (hit && hit->t < s.distance)
		return (true);
	return (false);
}

t_tuple	shade(t_minirt *minirt, t_inter_comp *intersect_comp)
{
	t_tuple		res;
	t_tuple		final_res;
	t_bool		shadow;
	int			i;

	i = -1;
	final_res = (t_tuple){0};
	while (++i < minirt->light_count)
	{
		shadow = is_in_shadow(minirt, intersect_comp->point_adjusted, i);
		res = lighting(intersect_comp, minirt->lights[i], shadow, minirt);
		final_res = add_vectors(&final_res, &res);
	}
	final_res = add_vectors(&final_res, &minirt->ambient->color);
	return (final_res);
}

t_tuple	color_at(t_minirt *minirt, t_ray *ray)
{
	t_intersection	*hit;
	t_intersects	intersections;
	t_inter_comp	computations;
	t_tuple			final_color;

	intersections = intersect_enivornment(minirt, ray);
	hit = best_hit(&intersections);
	if (hit == NULL)
		return (return_tuple(0, 0, 0, COLOR));
	computations = precompute_intersect(minirt, &intersections, hit, ray);
	final_color = shade(minirt, &computations);
	return (final_color);
}
