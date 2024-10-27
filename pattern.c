/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/27 22:44:25 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	create_pattern(t_tuple color_one, t_tuple color_two, int scale)
{
	t_pattern	pattern;

	pattern.color_one = color_one;
	pattern.color_two = color_two;
	pattern.pattern_scale = scale;
	return (pattern);
}

t_tuple	pattern_at_point(t_pattern pattern, t_tuple point)
{
	if ((int)floor(point.x * pattern.pattern_scale) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}

t_tuple	checkerboard(t_pattern pattern, t_tuple point)
{
	int	x;
	int	y;
	int	z;

	x = floor(point.x * pattern.pattern_scale);
	y = floor(point.y * pattern.pattern_scale);
	z = floor(point.z * pattern.pattern_scale);
	if ((x + y + z) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}

double	*sphere_uv(t_tuple point)
{
	double	theta;
	double	phi;
	double	*uv;

	theta = acos(-point.y);
	phi = atan2(point.z, point.x) + PI;
	uv = malloc(sizeof(double) * 2);
	uv[0] = phi / (2 * PI);
	uv[1] = theta / PI;
	return (uv);
}

t_tuple	checkerboard_sphere(t_pattern pattern, t_inter_comp *intersection)
{
	t_tuple	point;
	double	u;
	double	v;
	int		u_scaled;
	int		v_scaled;

	point = tuple_mult_fast(intersection->obj->inverse_mat, &intersection->point);
	u = 0.5 + (atan2(point.z, point.x) / (2 * PI));
	// v = 0.5 - (asin(point.y) * PI);
	v = 0.5 - (asin(point.y) + M_PI_2) / M_PI;
	u_scaled = floor(u * pattern.pattern_scale);
	v_scaled = floor(v * pattern.pattern_scale);
	if ((u_scaled + v_scaled) % 2 == 0)
	{
		return (pattern.color_one);
	}
	return (pattern.color_two);
}