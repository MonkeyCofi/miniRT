/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/08 21:20:07 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	draw_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*p;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		p = mlx->img.img_addr + (y * mlx->img.line_length) + \
			(x * (mlx->img.bpp / 8));
		*(unsigned int *)p = color;
	}
	return ;
}

void	print_4d_points(float points[4][4])
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("%.3f ", points[i][j]);
		printf("\n");
	}
}

t_ray	*ray_per_pixel(t_camera *camera, int px, int py)
{
	float	x_offset;
	float	y_offset;
	float	world_x;
	float	world_y;
	t_4dmat	*camera_inverse;
	t_tuple	*pixel;
	t_tuple	*origin;
	t_tuple	direction;
	t_tuple	temp;
	
	x_offset = (px + 0.5) * camera->pixel_size;
	y_offset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - x_offset;
	world_y = camera->half_height - y_offset;
	if (inverse_mat(camera->view_matrix, &camera_inverse) == false)
		return (NULL);
	temp = return_tuple(world_x, world_y, -1, POINT);
	pixel = tuple_mult(camera_inverse, &temp);
	temp = return_tuple(0, 0, 0, POINT);
	origin = tuple_mult(camera_inverse, &temp);
	direction = subtract_tuples(origin, pixel);
	normalize(&direction);
	return (create_ray(return_tuple(origin->x, origin->y, origin->z, origin->w), direction));
}
t_mater	*create_default_material()
{
	t_mater	*return_material;

	return_material = ft_calloc(1, sizeof(t_mater));
	if (!return_material)
		return (NULL);
	return_material->ambient = 0.1;
	return_material->diffuse = 0.9;
	return_material->specular = 0.9;
	return_material->shine = 200;
	return_material->color = return_color(1, 1, 1, 1);
	return (return_material);
}

t_mater	*create_material(t_color color, float diffuse, float ambient, float specular, float shine)
{
	t_mater	*ret_mat;

	ret_mat = ft_calloc(1, sizeof(t_mater));
	if (!ret_mat)
		return (NULL);
	ret_mat->color = color;
	ret_mat->diffuse = diffuse;
	ret_mat->ambient = ambient;
	ret_mat->specular = specular;
	ret_mat->shine = shine;
	return (ret_mat);
}

t_4dmat	*view_transform(t_tuple *to, t_tuple *from, t_tuple *up)
{
	t_tuple	forward_vec;
	t_tuple	left_vec;
	t_tuple	real_up;
	t_4dmat	*orientation;
	t_4dmat	transl8;
	t_4dmat	*res;
	t_tuple	up_normalized;
	float	points[4][4] = {};
	
	forward_vec = subtract_tuples(from, to);
	up_normalized = return_tuple(up->x, up->y, up->z, VECTOR);
	normalize(&up_normalized);
	normalize(&forward_vec);
	left_vec = cross_product(&forward_vec, &up_normalized);
	real_up = cross_product(&left_vec, &forward_vec);
	points[0][0] = left_vec.x;
	points[0][1] = left_vec.y;
	points[0][2] = left_vec.z;
	points[1][0] = real_up.x;
	points[1][1] = real_up.y;
	points[1][2] = real_up.z;
	points[2][0] = -forward_vec.x;
	points[2][1] = -forward_vec.y;
	points[2][2] = -forward_vec.z;
	points[3][3] = 1;
	orientation = create_4dmat(points);
	transl8 = translation_mat(-from->x, -from->y, -from->z);
	res = mat4d_mult(orientation, &transl8);
	free(orientation);
	return (res);
}

t_tuple	shade(t_minirt *minirt, t_inter_comp *intersect_comp)
{
	return (lighting(intersect_comp->obj->material, minirt->lights[0], intersect_comp->point, intersect_comp->eye_vec, *intersect_comp->normal_vec));
}

t_tuple	color_at(t_mlx *mlx, t_minirt *minirt, t_ray *ray, int i)
{
	t_intersects	*intersections;
	t_inter_comp	*computations;
	t_tuple			final_color;
	float			hit;

	intersections = intersect_enivornment(mlx, minirt, ray, minirt->spheres[i]);
	hit = best_hit(intersections);
	if (hit == -1)
		return (return_tuple(0, 0, 0, COLOR));
	computations = precompute_intersect(intersections, &intersections->intersections[intersections->intersection_count], ray, minirt->spheres[i]);
	final_color = shade(minirt, computations);
	return (final_color);
}

int	get_key_pressed(int keycode, t_mlx *mlx, t_sphere *sphere)
{
	if (keycode == PLUS)
		transform_sphere(sphere, scale, return_tuple(1, 2, 1, POINT));
	else if (keycode == ESC)
		exit(1);
	(void)mlx;
	return (0);
}

t_minirt	*init_default(t_mlx *mlx)
{
	t_minirt	*minirt;
	
	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		return (NULL);
	minirt->spheres = ft_calloc(2, sizeof(t_sphere *));
	if (!minirt->spheres)
	{
		free(minirt);
		return (NULL);
	}
	minirt->lights = ft_calloc(1, sizeof(t_light *));
	if (!minirt->lights)
	{
		free(minirt->spheres);
		free(minirt);
		return (NULL);
	}
	
	/* LIGHT */
	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
	if (!minirt->lights[0])
		return (NULL);
	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	minirt->lights[0]->position = return_tuple(-10, 10, -10, POINT);
	/* LIGHT */
	
	/* FIRST SPHERE */
	minirt->spheres[0] = ft_calloc(1, sizeof(t_sphere));
	if (!minirt->spheres[0])
		return (NULL);
	t_color	c;
	c.colors = return_tuple(0.8, 1, 0.6, COLOR);
	minirt->spheres[0]->material = create_material(c, 0.7, 0.1, 0.2, 200);
	minirt->spheres[0]->radius = 0.5;
	minirt->spheres[0]->center = return_tuple(0, 0, 0, POINT);
	/* FIRST SPHERE */
	
	/* SECOND SPHERE */
	minirt->spheres[1] = create_sphere(0, 0, 0, create_default_material());
	minirt->spheres[1]->radius = 1;
	minirt->spheres[1]->center = return_tuple(0, 0, 0, POINT);
	transform_sphere(minirt->spheres[1], scale, return_tuple(0.5, 0.5, 0.5, POINT));
	/* SECOND SPHERE */

	minirt->mlx = mlx;
	minirt->object_count = 2;
	return (minirt);
}

void	render(t_mlx *mlx, t_camera *camera, t_minirt *minirt)
{
	int		i;
	int		j;
	t_ray	*ray;

	i = -1;
	while (++i < camera->horizontal_canv_size)
	{
		j = -1;
		while (++j < camera->vertical_canv_size)
		{
			ray = ray_per_pixel(camera, j, i);
			t_tuple color = color_at(mlx, minirt, ray, 0);
			t_color c;
			c.colors = return_tuple(color.x, color.y, color.z, COLOR);
			//printf("Color: ");
			//print_tuple_points(&c.colors);
			draw_pixel(mlx, j, i, get_ray_color(&c));
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img.img, 0, 0);
}

//int main(void)
//{
//	t_minirt		*minirt;
//	t_mlx			mlx;

//	init_mlx(&mlx);
//	minirt = init_default(&mlx);
//	render_sphere(&mlx, minirt);
//	mlx_loop(mlx.mlx);
//}

int main(void)
{
	t_mater *material;
	t_sphere *sphere;
	t_tuple	*normal_test;
	
	material = create_default_material();
	sphere = create_sphere(0, 0, 0, material);
	
	transform_sphere(sphere, translate, return_tuple(0, 1, 0, POINT));
	normal_test = normal_pos(sphere, return_tuple(0, 1.70711, -0.70711, POINT));
	print_tuple_points(normal_test);
	
	free(material);
	free(sphere);
}