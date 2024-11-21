/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/21 21:12:35 by pipolint         ###   ########.fr       */
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
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	i = -1;
	m->tex_colors = ft_calloc(m->xpm_height, sizeof(t_tuple *));
	while (++i < m->xpm_height)
	{
		j = -1;
		m->tex_colors[i] = ft_calloc(m->xpm_width, sizeof(t_tuple));
		while (++j < m->xpm_width)
		{
			unsigned int *color = (unsigned int *)m->xpm.img_addr + ((i * m->xpm.line_length) + (j * (m->xpm.bpp / 8)));
			r = ((int)color >> 16) & 0xff;
			g = ((int)color >> 8) & 0xff;
			b = ((int)color) & 0xff;
			m->tex_colors[i][j].a = 1;
			m->tex_colors[i][j].r = r;
			m->tex_colors[i][j].g = g;
			m->tex_colors[i][j].b = b;
		}
	}
}

t_tuple	texture_sphere(t_inter_comp *intersection, t_ppm *tex)
{
	t_tuple	point;
	int		u_scaled;
	int		v_scaled;
	double	u;
	double	v;

	point = tuple_mult_fast(&intersection->obj->inverse_mat, &intersection->point);
	u = 0.5 + (atan2(point.z, point.x) / (2 * PI));
	v = 0.5 - (asin(point.y) + (PI / 2)) / PI;
	u_scaled = (int)fabs(u * (tex->width - 1)) % (tex->width - 1);
	v_scaled = (int)fabs(v * (tex->height - 1)) % (tex->height - 1);
	//printf("u %d v %d\n", u_scaled, v_scaled);
	return (tex->colors[u_scaled][v_scaled]);
}

t_tuple	texture_plane(t_inter_comp *intersection, t_ppm *tex)
{
	double	u;
	double	v;
	int		tex_x;
	int		tex_y;
	t_tuple	final_color;

	u = intersection->point.x;
	v = intersection->point.z;
	tex_x = ((int)fabs(u * (intersection->m->xpm_width - 1))) % (intersection->m->xpm_width - 1);
	tex_y = ((int)fabs(v * (intersection->m->xpm_height - 1))) % (intersection->m->xpm_height - 1);
	final_color.x = (intersection->m->tex_colors[tex_y][tex_x].r / 128) - 1;
	final_color.y = (intersection->m->tex_colors[tex_y][tex_x].g / 128) - 1;
	final_color.z = (intersection->m->tex_colors[tex_y][tex_x].b / 128) - 1;
	final_color.w = COLOR;
	(void)tex;
	return (final_color);
	//return (intersection->m->tex_colors[tex_y][tex_x]);
}

t_tuple	normal_from_sample(t_inter_comp *intersection)
{
	t_tuple	tangent;
	t_tuple	bitangent;
	t_tuple	n;
	t_4dmat	matrix;
	t_tuple	tangent_normal;

	tangent = return_vector(1, 0, 0);
	bitangent = return_vector(0, 1, 0);
	n = intersection->normal_vec;
	matrix = identity();
	tangent_normal = texture_plane(intersection, intersection->ppm);
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

t_tuple	map_sample(t_ppm *ppm, double *uv)
{
	t_tuple	color;
	t_tuple	ret;

	//color = ppm->colors[uv[0]][uv[]];
	ret.x = (color.r / 127.5) - 1;
	ret.y = (color.g / 127.5) - 1;
	ret.z = (color.b / 127.5) - 1;
	(void)ppm;
	(void)uv;
	return (ret);
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
