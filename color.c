/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:19:36 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/29 21:54:18 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minirt.h"

void	set_min_max(t_tuple *color)
{
	if (color->r < 0)
		color->r = 0;
	else if (color->r > 1)
		color->r = 1;
	if (color->g < 0)
		color->g = 0;
	else if (color->g > 1)
		color->g = 1;
	if (color->b < 0)
		color->b = 0;
	else if (color->b > 1)
		color->b = 1;
}

//t_color	return_color(double red, double green, double blue)
//{
//	t_color	ret_color;

//	ret_color.colors.r = red;
//	ret_color.colors.g = green;
//	ret_color.colors.b  = blue;
//	return (ret_color);
//}

uint32_t	get_ray_color(t_color	*color)
{
	uint32_t		res;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;

	set_min_max(&color->colors);
	r = color->colors.r * 255;
	g = color->colors.g * 255;
	b = color->colors.b * 255;
	a = color->colors.a;
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

static inline t_bool	is_in_shadow(t_minirt *minirt, t_tuple point, int light_index)
{
	t_intersection	*hit;
	t_intersects	intersect;
	t_tuple			direction;
	t_tuple			new_point;
	t_ray			ray;
	double			distance;
	
	new_point = (t_tuple){0};
	new_point = subtract_tuples(&point, &minirt->lights[light_index]->position);
	direction = return_tuple(new_point.x, new_point.y, new_point.z, VECTOR);
	normalize(&direction);
	distance = magnitude(&direction);
	ray = create_ray_static(point, direction);
	intersect = intersect_enivornment(minirt, &ray);
	hit = best_hit(&intersect);
	if (hit && hit->t < distance)
		return (true);
	return (false);
}

t_tuple	shade(t_minirt *minirt, t_inter_comp *intersect_comp)
{
	t_tuple	res;
	t_tuple	final_res;
	t_bool	shadow;
	int		i;

	i = -1;
	final_res = (t_tuple){0};
	while (++i < minirt->light_count)
	{
		shadow = is_in_shadow(minirt, intersect_comp->point_adjusted, i);
		res = lighting(intersect_comp, minirt->lights[i], intersect_comp->point_adjusted, intersect_comp->eye_vec, intersect_comp->normal_vec, shadow);
		//res = lighting(intersect_comp->obj, minirt->lights[i], intersect_comp->point_adjusted, intersect_comp->eye_vec, intersect_comp->normal_vec, shadow);
		final_res = add_vectors(&final_res, &res);
		scalar(&final_res, minirt->lights[i]->brightness);
	}
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

//t_tuple	color_at_temp(t_minirt *minirt, t_ray *ray)
//{
//	t_intersection	*hit;
//	t_intersects	*intersections;
//	t_inter_comp	*computations;
//	t_tuple			final_color;

//	intersections = intersect_enivornment(minirt, ray);
//	hit = best_hit(intersections);
//	if (hit == NULL)
//		return (return_tuple(0, 0, 0, COLOR));
//	computations = precompute_intersect(intersections, hit, ray);
//	final_color = shade(minirt, computations);
//	return (final_color);
//}
