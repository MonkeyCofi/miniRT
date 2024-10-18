/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:19:36 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/18 19:53:51 by pipolint         ###   ########.fr       */
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

t_color	return_color(float red, float green, float blue, float alpha)
{
	t_color	ret_color;

	ret_color.colors.r = red;
	ret_color.colors.g = green;
	ret_color.colors.b  = blue;
	ret_color.colors.a = alpha;
	return (ret_color);
}

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

t_tuple	shade(t_minirt *minirt, t_inter_comp *intersect_comp)
{
	t_tuple	res;
	t_tuple	final_res;
	t_tuple	point_slight;
	int		i;

	i = -1;
	ft_bzero(&final_res, sizeof(t_tuple));
	while (++i < minirt->light_count)
	{
		point_slight = add_vectors(&intersect_comp->point, intersect_comp->normal_vec);
		res = lighting(intersect_comp->material, minirt->lights[i], return_scalar(&point_slight, EPSILON), intersect_comp->eye_vec, *intersect_comp->normal_vec, 
			is_in_shadow(minirt, point_slight, i));
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
