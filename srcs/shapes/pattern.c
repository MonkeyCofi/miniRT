/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/25 20:30:28 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*create_pattern(t_tuple color_one, t_tuple color_two, int scale, t_pattern *pattern)
{
	pattern->color_one = color_one;
	pattern->color_two = color_two;
	pattern->pattern_scale = scale;
	return (pattern);
}

// go through the xpm file and fill an array ofcolors
void	fill_colors(t_minirt *m)
{
	int		i;
	int		j;
	char	*pixel;
	int		r;
	int		g;
	int		b;

	i = -1;
	m->tex_colors = ft_calloc(m->xpm_height, sizeof(t_tuple *));
	while (++i < m->xpm_height)
	{
		j = -1;
		m->tex_colors[i] = ft_calloc(m->xpm_width, sizeof(t_tuple));
		while (++j < m->xpm_width)
		{
			pixel = m->xpm.img_addr + ((i * m->xpm.line_length) + (j * (m->xpm.bpp / 8)));
			r = pixel[0] >> 16 & 0xff;
			g = pixel[1] >> 8 & 0xff;
			b = pixel[2] & 0xff;
			m->tex_colors[i][j].a = 1.0;
			m->tex_colors[i][j].r = (double)r;
			m->tex_colors[i][j].g = (double)g;
			m->tex_colors[i][j].b = (double)b;
			//printf("red %f green %f blue %f\n", m->tex_colors[i][j].r, m->tex_colors[i][j].g, m->tex_colors[i][j].b);
		}
	}
}

t_tuple	texture_sphere(t_inter_comp *intersection)
{
	t_tuple	point;
	t_tuple	color;
	int		u_scaled;
	int		v_scaled;
	double	u;
	double	v;

	point = tuple_mult_fast(&intersection->obj->inverse_mat, &intersection->point);	// transform the point into world space
	u = 0.5 + (atan2(point.z, point.x) / (2 * PI));
	v = 0.5 - (asin(point.y) / PI);
	//if (u < 0)
	//	u += 1;
	//if (v < 0)
	//	v += 1;
	u_scaled = (int)(u * (intersection->m->xpm_width)) % (intersection->m->xpm_width);
	v_scaled = (int)(v * (intersection->m->xpm_height)) % (intersection->m->xpm_height);
	color = intersection->m->tex_colors[v_scaled][u_scaled];
	color.r = (color.r / 255) * 2 - 1;
	color.g = (color.g / 255) * 2 - 1;
	color.b = (color.b / 255) * 2 - 1;
	return (color);
}

t_tuple	texture_plane(t_inter_comp *intersection, t_ppm *tex)
{
	double	u;
	double	v;
	int		tex_x;
	int		tex_y;
	t_tuple	final_color;

	u = fmod(intersection->point.x, 1);
	v = fmod(intersection->point.z, 1);
	if (u < 0)
		u += 1.0;
	if (v < 0)
		v += 1.0;
	tex_x = floor((int)(u * (intersection->m->xpm_width - 1)) % intersection->m->xpm_width);
	tex_y = floor((int)(v * (intersection->m->xpm_height - 1)) % intersection->m->xpm_height);
	final_color.r = (intersection->m->tex_colors[tex_y][tex_x].r / 255) * 2 - 1;
	final_color.g = (intersection->m->tex_colors[tex_y][tex_x].g / 255) * 2 - 1;
	final_color.b = (intersection->m->tex_colors[tex_y][tex_x].b / 255) * 2 - 1;
	final_color.w = COLOR;
	(void)tex;
	return (final_color);
}

t_tuple	normal_from_sample(t_inter_comp *intersection)
{
	t_tuple	tangent;
	t_tuple	bitangent;
	t_tuple	n;
	t_4dmat	matrix;
	t_tuple	tangent_normal;
	double	theta;

	theta = atan2(intersection->normal_vec.z, intersection->normal_vec.x);
	n = intersection->normal_vec;
	tangent = return_vector(-sin(theta), 0, cos(theta));
	normalize(&tangent);
	bitangent = cross_product(&n, &tangent);
	matrix = identity();
	if (intersection->type == PLANE)
		tangent_normal = texture_plane(intersection, intersection->ppm);
	else
		tangent_normal = texture_sphere(intersection);
	//normalize(&tangent_normal);
	matrix.m11 = tangent.x;
	matrix.m21 = tangent.y;
	matrix.m31 = tangent.z;
	matrix.m12 = bitangent.x;
	matrix.m22 = bitangent.y;
	matrix.m32 = bitangent.z;
	matrix.m13 = n.x;
	matrix.m23 = n.y;
	matrix.m33 = n.z;
	return (tuple_mult_fast(&matrix, &tangent_normal));
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

	point = tuple_mult_fast(&intersection->obj->inverse_mat, &intersection->point);
	u = 0.5 + (atan2(point.z, point.x) / (2 * PI));
	// v = 0.5 - (asin(point.y) * PI);
	v = 0.5 - (asin(point.y) + (PI / 2)) / PI;
	//v = 0.5 - (asin(point.y) + (M_PI_2)) / M_PI;
	u_scaled = floor(u * pattern.pattern_scale);
	v_scaled = floor(v * pattern.pattern_scale);
	if ((u_scaled + v_scaled) % 2 == 0)
		return (pattern.color_one);
	return (pattern.color_two);
}
t_tuple checkerboard_cylinder(t_pattern pattern, t_inter_comp *intersection)
{
    t_tuple point;
    double u;
	double v;
    int u_scaled;
	int v_scaled;
    
    point = tuple_mult_fast(&intersection->obj->inverse_mat, &intersection->point);
    u = 0.5 + (atan2(point.z, point.x) / (2 * PI)); //basedon angle aroud cylinder

	// v based off height, the normalized
    double min_y = ((t_cylinder *)(intersection->obj->shape))->minimum;
    double max_y = ((t_cylinder *)(intersection->obj->shape))->maximum;
    double height = max_y - min_y;
	// v to fit 0,1
    v = (point.y - min_y) / height;
    u_scaled = floor(u * pattern.pattern_scale);
    v_scaled = floor(v * pattern.pattern_scale);
    if ((u_scaled + v_scaled) % 2 == 0)
        return pattern.color_one;
    return pattern.color_two;
}

t_tuple checkerboard_cap(t_pattern pattern, t_tuple point)
{
	int x;
	int z;
	x = floor((point.x + 1.0) * 0.2 * pattern.pattern_scale);
	z = floor((point.z + 1.0) * 0.2 * pattern.pattern_scale); 
	if ((x + z) % 2 == 0)
		return pattern.color_one;
	return pattern.color_two;
}
