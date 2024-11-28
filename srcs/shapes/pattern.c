/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/28 10:37:35 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*create_pattern(t_tuple color_one, t_tuple color_two, \
int scale, t_pattern *pattern)
{
	pattern->color_one = color_one;
	pattern->color_two = color_two;
	pattern->pattern_scale = scale;
	return (pattern);
}

t_tuple	texture_sphere(t_inter_comp *intersection, t_ppm *tex)
{
	t_tuple	point;
	int		u_scaled;
	int		v_scaled;
	double	u;
	double	v;

	point = tuple_mult_fast(&intersection->obj->inverse_mat, \
	&intersection->point);
	u = 0.5 + (atan2(point.z, point.x) / (2 * PI));
	v = 0.5 - (asin(point.y) + (PI / 2)) / PI;
	printf("u %f v %f\n", u, v);
	u_scaled = floor(u * tex->width - 1);
	v_scaled = floor(v * tex->width - 1);
	printf("x %d y %d\n", u_scaled, v_scaled);
	return (tex->colors[u_scaled][v_scaled]);
}

t_tuple	texture_plane(t_inter_comp *intersection, t_ppm *tex)
{
	double	u;
	double	v;
	int		tex_x;
	int		tex_y;

	u = intersection->point.x;
	v = intersection->point.z;
	printf("u %f v %f\n", u, v);
	tex_x = (u * tex->width - 1);
	tex_y = (v * tex->height - 1);
	printf("x %d y %d\n", tex_x, tex_y);
	return (tex->colors[tex_y][tex_x]);
}

t_tuple	pattern_at_point(t_pattern pattern, t_tuple point)
{
	if ((int)floor(point.x * pattern.pattern_scale) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}

t_tuple	checkerboard(t_pattern pattern, t_tuple point, t_tuple plane_normal)
{
	t_checkerboard s;

	s.u = 0;
	s.v = 0;
	if (fabs(plane_normal.y) == 1) // Horizontal plane
	{
		s.u = modf(point.x, &s.u_scaled);
		s.v = modf(point.z, &s.v_scaled);
	}
	else if (fabs(plane_normal.x) == 1) // Vertical plane, X-oriented
	{
		s.u = modf(point.y, &s.u_scaled);
		s.v = modf(point.z, &s.v_scaled);
	}
	else if (fabs(plane_normal.z) == 1) // Vertical plane, Z-oriented
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

double vect_length(t_tuple *s)
{
    return sqrt(s->x * s->x + s->y * s->y + s->z * s->z);
}

t_tuple	checkerboard_sphere(t_pattern pattern, t_inter_comp *intersection)
{
	t_tuple	point;
	double	u;
	double	v;
	int		u_scaled;
	int		v_scaled;
	double	radius;
	double	phi;

	point = tuple_mult_fast(&intersection->obj->inverse_mat, \
	&intersection->point);
	u = 0.5 + (atan2(point.z, point.x) / (2 * M_PI));
	radius = vect_length(&point);
	phi = acos(point.y / radius);
	v = 1 - (phi / M_PI);
	u_scaled = floor(u * pattern.pattern_scale);
	v_scaled = floor(v * pattern.pattern_scale);
	if ((u_scaled + v_scaled) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}

t_tuple	checkerboard_cylinder(t_pattern pattern, t_inter_comp *intersection)
{
	t_tuple	point;
	double	u;
	double	v;
	int		u_scaled;
	int		v_scaled;
	double	min_y;
	double	max_y;
	double	height;

	point = tuple_mult_fast(&intersection->obj->inverse_mat, \
	&intersection->point);
	u = 0.5 + (atan2(point.z, point.x) / (2 * M_PI));
	min_y = ((t_cylinder *)(intersection->obj->shape))->minimum;
	max_y = ((t_cylinder *)(intersection->obj->shape))->maximum;
	height = max_y - min_y;
	v = (point.y - min_y) / height;
	u_scaled = floor(u * pattern.pattern_scale);
	v_scaled = floor(v * pattern.pattern_scale);
	if ((u_scaled + v_scaled) % 2 == 0)
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
