/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/04 19:32:03 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*create_pattern(t_tuple one, t_tuple two, int scale, \
	t_pattern *pattern)
{
	pattern->color_one = one;
	pattern->color_two = two;
	pattern->pattern_scale = scale;
	return (pattern);
}

t_tuple	checkerboard(t_pattern pattern, t_tuple point, t_tuple plane_normal)
{
	t_checkerboard	s;

	s.u = 0;
	s.v = 0;
	if (fabs(plane_normal.y) == 1)
	{
		s.u = modf(point.x, &s.u_scaled);
		s.v = modf(point.z, &s.v_scaled);
	}
	else if (fabs(plane_normal.x) == 1)
	{
		s.u = modf(point.y, &s.u_scaled);
		s.v = modf(point.z, &s.v_scaled);
	}
	else if (fabs(plane_normal.z) == 1)
	{
		s.u = modf(point.x, &s.u_scaled);
		s.v = modf(point.y, &s.v_scaled);
	}
	s.u_scaled = floor(s.u * pattern.pattern_scale);
	s.v_scaled = floor(s.v * pattern.pattern_scale);
	if (((int)s.u_scaled + (int)s.v_scaled) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}

t_tuple	checkerboard_sphere(t_pattern pattern, t_inter_comp *intersection)
{
	t_tuple			point;
	t_checkerboard	s;
	double			radius;
	double			phi;

	point = tuple_mult_fast(&intersection->obj->inverse_mat, \
	&intersection->point);
	s.u = 0.5 + (atan2(point.z, point.x) / (2 * M_PI));
	radius = magnitude(&point);
	phi = acos(point.y / radius);
	s.v = 1 - (phi / M_PI);
	s.u_scaled = floor(s.u * pattern.pattern_scale);
	s.v_scaled = floor(s.v * pattern.pattern_scale);
	if ((int)(s.u_scaled + s.v_scaled) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}

t_tuple	checkerboard_cylinder(t_pattern pattern, t_inter_comp *intersection)
{
	t_tuple			point;
	t_checkerboard	s;
	double			min_y;
	double			max_y;
	double			height;

	point = tuple_mult_fast(&intersection->obj->inverse_mat, \
		&intersection->point);
	s.u = 0.5 + (atan2(point.z, point.x) / (2 * M_PI));
	min_y = ((t_cylinder *)(intersection->obj->shape))->minimum;
	max_y = ((t_cylinder *)(intersection->obj->shape))->maximum;
	height = max_y - min_y;
	s.v = (point.y - min_y) / height;
	s.u_scaled = floor(s.u * pattern.pattern_scale);
	s.v_scaled = floor(s.v * pattern.pattern_scale);
	if ((int)(s.u_scaled + s.v_scaled) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}

t_tuple	checkerboard_cap(t_pattern pattern, t_tuple point)
{
	int	x;
	int	z;

	x = floor((point.x + 1.0) * 0.2 * pattern.pattern_scale);
	z = floor((point.z + 1.0) * 0.2 * pattern.pattern_scale);
	if ((x + z) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}
