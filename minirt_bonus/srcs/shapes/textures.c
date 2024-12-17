/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 19:29:29 by pipolint          #+#    #+#             */
/*   Updated: 2024/12/10 19:00:03 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	*get_uv_sphere(t_inter_comp *inter, double *phi, double *theta)
{
	t_sphere	*sphere;
	t_tuple		point;
	t_mater		*mat;
	int			*tex_uv;

	point = subtract_tuples(&inter->obj->coords, &inter->point);
	sphere = inter->obj->shape;
	*phi = atan2(point.z, point.x);
	*theta = acos(point.y / sphere->radius);
	mat = inter->material;
	tex_uv = calloc_and_check(2, sizeof(int), inter->m, \
		"Error\nFailed to allocate memory\n");
	tex_uv[0] = ((int)(((-(*phi) + PI) / (2.0 * PI)) * \
		mat->texture->img_width) % mat->texture->img_width);
	tex_uv[1] = ((int)((*theta / PI) * \
		mat->texture->img_height) % mat->texture->img_height);
	return (tex_uv);
}

t_tuple	texture_sphere(t_inter_comp *inter, double *phi, double *theta)
{
	uint32_t	color;
	t_tuple		final_res;
	t_mater		*mat;
	char		*pixel;
	int			*tex_uv;

	tex_uv = get_uv_sphere(inter, phi, theta);
	mat = inter->material;
	pixel = mat->texture->img_addr + (tex_uv[1] * mat->texture->line_length) \
		+ (tex_uv[0] * (mat->texture->bpp / 8));
	color = *(uint32_t *)pixel;
	final_res.a = 1.0;
	final_res.r = color >> 16 & 0xFF;
	final_res.g = color >> 8 & 0xFF;
	final_res.b = color & 0xFF;
	normalize(&final_res);
	free(tex_uv);
	return (final_res);
}

static t_4dmat	construct_tbn(t_inter_comp *inter, \
	const double *const phi, const double *const theta)
{
	t_4dmat		matrix;
	t_sphere	*sphere;
	t_tuple		point;

	point = subtract_tuples(&inter->obj->coords, &inter->point);
	matrix = identity();
	sphere = inter->obj->shape;
	matrix.m11 = 2 * PI * point.z;
	matrix.m21 = 0;
	matrix.m31 = -2 * PI * point.x;
	matrix.m12 = PI * point.y * cos(*phi);
	matrix.m22 = -sphere->radius * PI * sin(*theta);
	matrix.m32 = PI * point.y * sin(*phi);
	matrix.m13 = inter->normal_vec.x;
	matrix.m23 = inter->normal_vec.y;
	matrix.m33 = inter->normal_vec.z;
	return (matrix);
}

t_tuple	normal_from_sample(t_inter_comp *intersection)
{
	t_tuple	tangent_normal;
	t_tuple	res;
	t_4dmat	matrix;
	double	theta;
	double	phi;

	tangent_normal = texture_sphere(intersection, &phi, &theta);
	matrix = construct_tbn(intersection, &phi, &theta);
	res = tuple_mult(&matrix, &tangent_normal);
	normalize(&res);
	return (res);
}
