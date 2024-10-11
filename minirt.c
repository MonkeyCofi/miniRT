/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/11 21:29:18 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt);

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
	return (create_ray(*origin, direction));
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

void	render(t_mlx *mlx, t_camera *camera, t_minirt *minirt)
{
	int		i;
	int		j;
	t_ray	*ray;

	i = -1;
	while (++i < camera->horizontal_canv_size - 1)
	{
		j = -1;
		while (++j < camera->vertical_canv_size - 1)
		{
			ray = ray_per_pixel(camera, j, i);
			t_tuple color = color_at(minirt, ray);
			t_color c;
			c.colors = return_tuple(color.x, color.y, color.z, COLOR);
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

//int main(void)
//{
//	t_mater *material;
//	t_sphere *sphere;
//	t_tuple	*normal_test;
//	t_ray	*ray;
	
//	material = create_default_material();
//	sphere = create_sphere(0, 0, 0, material);
	
//	transform_sphere(sphere, translate, return_tuple(0, 1, 0, POINT));
//	normal_test = normal_pos(sphere, return_tuple(0, 1.70711, -0.70711, POINT));
//	print_tuple_points(normal_test);
	
//	ray = create_ray(return_tuple(1, 2, 3, POINT), return_tuple(0, 1, 0, VECTOR));
//	//t_4dmat translate = translation_mat(3, 4, 5);
//	t_ray transformed = transform_ray(ray, scale, return_tuple(2, 3, 4, POINT), NULL);
//	printf("Origin: ");
//	print_tuple_points(&transformed.origin);
//	printf("Direction: ");
//	print_tuple_points(&transformed.direction);
	
//	free(material);
//	free(sphere);
//}

//int main(void)
//{
//	t_mlx mlx;
//	if (init_mlx(&mlx) == -1)
//		return (1);
//	t_minirt *world = init_default(&mlx);
//	t_ray *ray = create_ray(return_tuple(0, 0, -5, POINT), return_tuple(0, 0, 1, VECTOR));
//	t_tuple color = color_at(world, ray);
//	print_tuple_points(&color);

//	//t_intersection i = intersect(4, SPHERE, world->spheres[0], ray, none, return_tuple(0, 0, 0, POINT));
//	//t_inter_comp *comps = precompute_intersect(NULL, &i, ray);
//	//t_tuple c = shade(world, comps);
//	//print_tuple_points(&c);
//}

//int main(void)
//{
//	t_mlx mlx;
//	init_mlx(&mlx);
//	t_minirt* world = init_default(&mlx);
	
//	t_mater *floor_mat = create_default_material();
//	t_sphere *floor = create_sphere(0, 0, 0, floor_mat);
//	floor->transform = scaling_mat(10, 0.01, 10);
//	floor->material->color.colors = return_tuple(1, 0.9, 0.9, COLOR);
//	floor->material->specular = 0;
	
//	world->object_count = 7;
//	free(world->spheres);
//	world->spheres = ft_calloc(world->object_count, sizeof(t_sphere *));
//	t_mater *material = create_default_material();
//	t_sphere *sphere = create_sphere(0, 0, 0, material);
//	sphere->material->color.colors = return_tuple(0.1, 1, 0.5, COLOR);
//	sphere->transform = translation_mat(-0.5, 1, -0.5);
//	sphere->material->diffuse = 0.7;
//	sphere->material->specular = 0.3;
//	world->spheres[0] = sphere;

//	t_sphere *left_wall = create_sphere(0, 0, 0, NULL);
//	world->spheres[1] = floor;
//	left_wall->transform = translation_mat(0, 0, 5);
//	t_4dmat temp = y_rotation_mat(-PI / 4);
//	left_wall->transform = mat4d_mult_fast_static(&left_wall->transform, &temp);
//	temp = x_rotation_mat(PI / 2);
//	left_wall->transform = mat4d_mult_fast_static(&left_wall->transform, &temp);
//	temp = scaling_mat(10, 0.01, 10);
//	left_wall->transform = mat4d_mult_fast_static(&left_wall->transform, &temp);
//	left_wall->material = floor_mat;
//	world->spheres[2] = left_wall;
	
//	t_sphere *right_wall = create_sphere(0, 0, 0, floor_mat);
//	right_wall->transform = translation_mat(0, 0, 5);
//	temp = y_rotation_mat(PI / 4);
//	right_wall->transform = mat4d_mult_fast_static(&right_wall->transform, &temp);
//	temp = x_rotation_mat(PI / 2);
//	right_wall->transform = mat4d_mult_fast_static(&right_wall->transform, &temp);
//	temp = scaling_mat(10, 0.01, 10);
//	right_wall->transform = mat4d_mult_fast_static(&right_wall->transform, &temp);
//	world->spheres[3] = right_wall;
	
//	//t_camera camera = return_camera(WIDTH, HEIGHT, PI / 3, NULL);
//	t_camera camera = return_camera(WIDTH, HEIGHT, 1.5708, NULL);
//	t_tuple to = return_tuple(0, 1, 0, POINT);
//	t_tuple from = return_tuple(0, 1.5, -5, POINT);
//	t_tuple up = return_tuple(0, 1, 0, VECTOR);
//	camera.view_matrix = view_transform(&to, &from, &up);
//	//temp = y_rotation_mat(DEG_RAD(-30));
//	//camera.view_matrix = mat4d_mult_fast(camera.view_matrix, &temp);
//	//temp = translation_mat(-1.8, 0, 0);
//	//camera.view_matrix = mat4d_mult_fast(camera.view_matrix, &temp);
//	//temp = y_rotation_mat(DEG_RAD(-50));
//	//camera.view_matrix = mat4d_mult_fast(camera.view_matrix, &temp);
//	//temp = z_rotation_mat(DEG_RAD(-30));
//	//camera.view_matrix = mat4d_mult_fast(camera.view_matrix, &temp);
	
//	t_sphere *right = create_sphere(0, 0, 0, create_default_material());
//	right->transform = translation_mat(1.8, 0.5, 0.5); // * scaling(0.5, 0.5, 0.5);
//	temp = scaling_mat(0.5, 0.5, 0.5);
//	right->transform = mat4d_mult_fast_static(&right->transform, &temp);
//	right->material->color.colors = return_tuple(0.5, 1, 0.1, COLOR);
//	right->material->diffuse = 0.7;
//	right->material->specular = 0.3;
//	world->spheres[4] = right;
	
//	t_sphere *left = create_sphere(0, 0, 0, create_default_material());
//	left->transform = translation_mat(-1.5, 0.33, -0.75);
//	temp = scaling_mat(0.33, 0.33, 0.33);
//	left->transform = mat4d_mult_fast_static(&left->transform, &temp);
//	left->material->color.colors = return_tuple(1, 0.8, 0.1, COLOR);
//	left->material->diffuse = 0.7;
//	left->material->specular = 0.3;
//	world->spheres[5] = left;
	
//	t_mater *new = create_default_material();
//	t_sphere *extra = create_sphere(0, 0, 0, new);
//	new->ambient = 0.3;
//	new->specular = 0.6;
//	new->color.colors = return_tuple(0, 0.4, 0.5, COLOR);
//	extra->transform = translation_mat(0.5, 0.5, 0.2);
//	world->spheres[6] = extra;
	
//	//t_light light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(-3, 10, -10, POINT));
//	t_light light = create_light(return_tuple(0, 0, 0, COLOR), return_tuple(10, 10, 0.5, POINT));
//	//t_light light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(-10, 10, -10, POINT));
//	world->lights[1] = &light;
//	//world->lights[1] = &light;
//	world->light_count = 1;
//	//(void)light;
	
//	render(&mlx, &camera, world);
//	mlx_loop(&mlx.mlx);
//}

//int main(void)
//{
//	t_mlx 		mlx;
//	t_minirt 	*world;
//	t_camera	cam;
//	t_sphere	*sphere;
	
//	if (init_mlx(&mlx) == -1)
//	{
//		write(2, "Error: couldn't initialize mlx struct\n", 39);
//		return (1);
//	}
//	world = init_default(&mlx);
//	cam = return_camera(WIDTH, HEIGHT, DEG_RAD(45), NULL);
//	t_tuple to = return_tuple(0, 0, 0, POINT);
//	t_tuple from = return_tuple(-3, 0, -3, POINT);
//	t_tuple up = return_tuple(0, 1, 0, VECTOR);
//	cam.view_matrix = view_transform(&to, &from, &up);
//	t_4dmat temp2 = translation_mat(0, 0.5, 0);
//	t_4dmat *uwu = cam.view_matrix;
//	cam.view_matrix = mat4d_mult_fast(cam.view_matrix, &temp2);
//	free(uwu);
//	uwu = cam.view_matrix;
//	temp2 = x_rotation_mat(DEG_RAD(-45));
//	cam.view_matrix = mat4d_mult_fast(cam.view_matrix, &temp2);
//	free(uwu);
//	t_light light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(20, 10, 0, POINT));
//	t_light *temp = world->lights[0];
//	free(world->lights);
//	world->light_count++;
//	world->lights = ft_calloc(world->light_count, sizeof(t_light *));
//	world->lights[0] = temp;
//	world->lights[1] = &light;
	
//	t_mater	*sphere_mat = create_default_material();
//	sphere_mat->color.colors = return_tuple(0.5, 0.3, 0, COLOR);
//	sphere = create_sphere(0, 0, 0, sphere_mat);
//	sphere->transform = translation_mat(0.9, 0, 0.4);
//	world->spheres[1] = sphere;

//	t_mater *default_mat = create_default_material();
//	t_sphere *wall = create_sphere(0, 0, 0, default_mat);
//	wall->transform = scaling_mat(1.5, 1.5, 1.5);
//	t_4dmat temp_matrix = translation_mat(0, 0, 1.5);
//	wall->transform = mat4d_mult_fast_static(&wall->transform, &temp_matrix);
	
//	t_sphere *t1 = world->spheres[0];
//	t_sphere *t2 = world->spheres[1];
//	free(world->spheres);
//	world->spheres = ft_calloc(5, sizeof(t_sphere *));
//	world->spheres[0] = t1;
//	world->spheres[1] = t2;
//	//world->spheres[2] = wall;
//	world->object_count = 2;
	
//	render(&mlx, &cam, world);
//	mlx_loop(&mlx.mlx);
//}

int main(void)
{
	t_mlx mlx;
	init_mlx(&mlx);
	
	// world
	t_minirt *world = init_default(&mlx);
	
	// camera
	t_camera camera = return_camera(WIDTH, HEIGHT, DEG_RAD(90), NULL);
	t_tuple to = return_tuple(0, 0, 0, POINT);
	t_tuple from = return_tuple(0, 0, -1.5, POINT);
	t_tuple up = return_tuple(0, 1, 0, VECTOR);
	camera.view_matrix = view_transform(&to, &from, &up);
	
	free_shapes(world);
	
	world->object_count = 2;
	world->spheres = ft_calloc(world->object_count, sizeof(t_sphere *));
	
	//light
	t_light light = create_light(return_tuple(1, 1, 1, COLOR), return_tuple(0, 10, 0, POINT));
	t_light *temp = world->lights[0];
	free(world->lights);
	world->lights = ft_calloc(2, sizeof(t_light *));
	world->lights[0] = temp;
	world->lights[1] = &light;
	world->light_count = 2;
	
	// first sphere
	t_mater *material = create_default_material();
	material->color.colors = return_tuple(0.7, 0.4, 0.1, COLOR);
	t_sphere *first = create_sphere(0, 0 ,0, material);
	world->spheres[0] = first;
	
	t_mater *material2 = create_default_material();
	t_sphere *second = create_sphere(0, 0 ,0, material2);
	world->spheres[1] = second;
	material2->color.colors = return_tuple(0.7, 0.3, 0.1, COLOR);
	world->spheres[1]->transform = translation_mat(-0.3, 0.3, -0.2);
	t_4dmat uwu = scaling_mat(0.2, 0.2, 0.2);
	world->spheres[1]->transform = mat4d_mult_fast_static(&world->spheres[1]->transform, &uwu);

	render(&mlx, &camera, world);
	mlx_loop(&mlx.mlx);
}