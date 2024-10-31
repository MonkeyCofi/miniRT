/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:06 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/31 10:16:02 by ahaarij          ###   ########.fr       */
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

t_tuple	texture_sphere(t_tuple point, t_ppm *tex)
{
	double	*uv;
	int		tex_x;
	int		tex_y;
	
	uv = sphere_uv(point);
	tex_x = (uv[0] * tex->width - 1);
	tex_y = (uv[1] * tex->width - 1);
	//printf("getting texture\n");
	return (tex->colors[tex_y][tex_x]);
}

t_tuple	texture_plane(t_tuple point, t_ppm *tex)
{
	double	u;
	double	v;
	int		tex_x;
	int		tex_y;

	u = point.x * 10;
	v = point.z * 10;
	tex_x = (u * tex->width - 1);
	tex_y = (v * tex->width - 1);
	printf("getting texture\n");
	return (tex->colors[tex_y][tex_x]);
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
    
    point = tuple_mult_fast(intersection->obj->inverse_mat, &intersection->point);
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
