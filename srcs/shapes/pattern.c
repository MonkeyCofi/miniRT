/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/28 19:43:19 by pipolint         ###   ########.fr       */
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

t_tuple	texture_sphere(t_inter_comp *intersection, double *phi, double *theta)
{
	t_tuple		point;
	t_tuple		final_res;
	t_sphere	*sphere;
	char		*pixel;
	uint32_t	color;
	float		u;
	float		v;
	int			tex_u;
	int			tex_v;

	sphere = intersection->obj->shape;
	point = subtract_tuples(&intersection->obj->coords, &intersection->point);
	*phi = atan2(point.z, point.x);
	*theta = acos(point.y / sphere->radius);
	u = ((-(*phi) + PI) / (2.0 * PI));
	v = (*theta / PI);
	tex_u = floor((int)(u * intersection->material->texture->img_width) % intersection->material->texture->img_width);
	tex_v = floor((int)(v * intersection->material->texture->img_height) % intersection->material->texture->img_height);
	pixel = intersection->material->texture->img_addr + (tex_v * intersection->material->texture->line_length) + (tex_u * (intersection->material->texture->bpp / 8));
	color = *(uint32_t *)pixel;
	final_res.a = 1.0;
	final_res.r = color >> 16 & 0xFF;
	final_res.g = color >> 8 & 0xFF;
	final_res.b = color & 0xFF;
	normalize(&final_res);
	return (final_res);
}

t_tuple	texture_plane(t_inter_comp *intersection, t_ppm *tex)
{
	(void)intersection;
	(void)tex;
	return (return_vector(0, 0, 0));
}
//{
//	double		u;
//	double		v;
//	int			tex_x;
//	int			tex_y;
//	t_tuple		final_color;
//	char		*pixel;
//	uint32_t	color;

//	u = fmod(intersection->point.x, 1);
//	v = fmod(intersection->point.z, 1);
//	if (u < 0)
//		u += 1.0;
//	if (v < 0)
//		v += 1.0;
//	tex_x = floor((int)(u * (intersection->m->xpm_width)) % intersection->m->xpm_width);
//	tex_y = floor((int)(v * (intersection->m->xpm_height)) % intersection->m->xpm_height);
//	pixel = intersection->m->xpm.img_addr + (tex_y * intersection->m->xpm.line_length) + (tex_x * (intersection->m->xpm.bpp / 8));
//	color = *(uint32_t *)pixel;
//	final_color.r = color >> 16 & 0xFF;
//	final_color.g = color >> 8 & 0xFF;
//	final_color.b = color & 0xFF;
//	final_color.a = 1;
//	normalize(&final_color);
//	(void)tex;
//	return (final_color);
//}

t_tuple	normal_from_sample(t_inter_comp *intersection)
{
	t_tuple		tangent;
	t_tuple		bitangent;
	t_tuple		n;
	t_4dmat		matrix;
	t_tuple		tangent_normal;
	t_sphere	*sphere;
	double	theta = 0;
	double	phi = 0;

	sphere = intersection->obj->shape;
	if (intersection->type == PLANE)
		tangent_normal = texture_plane(intersection, intersection->ppm);
	else
		tangent_normal = texture_sphere(intersection, &phi, &theta);
	//normalize(&tangent_normal);
	t_tuple point = subtract_tuples(&intersection->obj->coords, &intersection->point);
	n = tuple_mult_fast(&intersection->obj->inverse_transpose, &intersection->normal_vec);
	//n = intersection->normal_vec;
	tangent.x = 2 * PI * point.z;
	tangent.y = 0;
	tangent.z = -2 * PI * point.x;
	bitangent.x = PI * point.y * cos(phi);
	bitangent.y = -sphere->radius * PI * sin(theta);
	bitangent.z = PI * point.y * sin(phi);
	normalize(&tangent);
	normalize(&bitangent);
	matrix = identity();
	matrix.m11 = tangent.x;
	matrix.m21 = tangent.y;
	matrix.m31 = tangent.z;
	matrix.m12 = bitangent.x;
	matrix.m22 = bitangent.y;
	matrix.m32 = bitangent.z;
	matrix.m13 = n.x;
	matrix.m23 = n.y;
	matrix.m33 = n.z;
	t_tuple	res = tuple_mult_fast(&matrix, &tangent_normal);
	normalize(&res);
	//print_tuple_points(&res);
	return (res);
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
