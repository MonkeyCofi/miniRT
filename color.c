/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:19:36 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/19 03:12:18 by ahaarij          ###   ########.fr       */
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

t_tuple	return_color(float red, float green, float blue, float alpha)
{
	t_tuple	ret_color;

	ret_color.r = red;
	ret_color.g = green;
	ret_color.b  = blue;
	ret_color.a = alpha;
	return (ret_color);
}

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

t_tuple	shade(t_minirt *minirt, t_inter_comp *intersect_comp)
{
	t_tuple	res;
	t_tuple	final_res;
	int		i;

	i = -1;
	ft_bzero(&final_res, sizeof(t_tuple));
	while (++i < minirt->light_count)
	{
		t_tuple test = add_vectors(&intersect_comp->point, intersect_comp->normal_vec);
		res = lighting(intersect_comp->material, minirt->lights[i], return_scalar(&test, EPSILON), intersect_comp->eye_vec, *intersect_comp->normal_vec, 
			is_in_shadow(minirt, test, i));
		final_res = add_vectors(&final_res, &res);
	}
	return (final_res);
}

t_tuple	color_at(t_minirt *minirt, t_ray *ray)
{
	t_intersects	*intersections;
	t_inter_comp	*computations;
	t_tuple			final_color;
	t_intersection	*hit;

	intersections = intersect_enivornment(minirt, ray);
	hit = best_hit(intersections);
	if (hit == NULL)
		return (return_tuple(0, 0, 0, COLOR));
	computations = precompute_intersect(intersections, hit, ray);
	final_color = shade(minirt, computations);
	return (final_color);
}
