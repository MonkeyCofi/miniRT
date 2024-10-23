/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/23 21:46:00 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

t_minirt	*init_minirt(t_mlx *mlx, int num_of_spheres, int num_of_lights)
{
	t_minirt	*ret;

	ret = ft_calloc(1, sizeof(t_minirt));
	if (!ret)
		return (NULL);
	ret->cam = ft_calloc(1, sizeof(t_camera));
	if (!ret->cam)
	{
		free(ret);
		return (NULL);
	}
	ret->spheres = ft_calloc(num_of_spheres, sizeof(t_sphere *));
	if (!ret->spheres)
	{
		free(ret->cam);
		free(ret);
		return (NULL);
	}
	ret->lights = ft_calloc(num_of_lights, sizeof(t_light *));
	if (!ret->lights)
	{
		free(ret->spheres);
		free(ret->cam);
		free(ret);
		return (NULL);
	}
	ret->mlx = mlx;
	//init_cam(ret);
	return (ret);
}

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (-1);
	mlx->img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!(mlx->img.img))
		return (-1);
	mlx->img.img_addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bpp, &mlx->img.line_length, &mlx->img.endian);
	if (!APPLE)
	{
		mlx_hook(mlx->win, 2, 1L << 0, escape, mlx);
	}
	else
	{
		mlx_hook(mlx->win, 2, 0, escape, mlx);
		mlx_hook(mlx->win, 17, 0, destroy, mlx);
	}
	return (1);
}

//t_minirt	*init_default(t_mlx *mlx)
//{
//	t_minirt	*minirt;
	
//	minirt = ft_calloc(1, sizeof(t_minirt));
//	if (!minirt)
//		return (NULL);
//	minirt->spheres = ft_calloc(2, sizeof(t_sphere *));
//	if (!minirt->spheres)
//	{
//		free(minirt);
//		return (NULL);
//	}
//	minirt->light_count = 3;
//	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
//	if (!minirt->lights)
//	{
//		free(minirt->spheres);
//		free(minirt);
//		return (NULL);
//	}
	
//	/* LIGHT */
//	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
//	if (!minirt->lights[0])
//		return (NULL);
//	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
//	minirt->lights[0]->position = return_tuple(-10, 10, -10, POINT);
	
//	minirt->lights[1] = ft_calloc(1, sizeof(t_light));
//	if (!minirt->lights[1])
//		return (NULL);
//	minirt->lights[1]->intensity.colors = return_tuple(0.2, 0.2, 0.2, COLOR);
//	minirt->lights[1]->position = return_tuple(0, -5, -5, POINT);
	
//	minirt->lights[2] = ft_calloc(1, sizeof(t_light));
//	if (!minirt->lights[2])
//		return (NULL);
//	minirt->lights[2]->intensity.colors = return_tuple(0.2, 0.2, 0.2, COLOR);
//	minirt->lights[2]->position = return_tuple(0, 10, 0, POINT);
	
	
//	/* LIGHT */
	
//	minirt->object_count = 1;
	
//	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));
	
//	t_sphere *sphere = create_sphere(0, 0, 0, create_default_material());
//	sphere->transform = scaling_mat(1.1, 1.1, 1.1);
//	minirt->shapes[0] = ft_calloc(1, sizeof(t_shape));
//	minirt->shapes[0]->shape = sphere;
//	minirt->shapes[0]->type = SPHERE;
	
//	//t_plane *plane = ft_calloc(1, sizeof(t_plane));
//	//plane->material = create_default_material();
//	//plane->transform = identity();
//	//plane->point = return_tuple(0, 0, 0, POINT);
	
//	//minirt->shapes[1] = ft_calloc(1, sizeof(t_shape));
//	//minirt->shapes[1]->shape = plane;
//	//minirt->shapes[1]->type = PLANE;

//	minirt->mlx = mlx;
//	return (minirt);
//}

t_minirt	* init_default(t_mlx *mlx)
{
	t_minirt	*minirt;
	t_4dmat		temp;
	
	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		return (NULL);
	minirt->spheres = ft_calloc(2, sizeof(t_sphere *));
	if (!minirt->spheres)
	{
		free(minirt);
		return (NULL);
	}
	minirt->light_count = 2;
	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
	if (!minirt->lights)
	{
		free(minirt->spheres);
		free(minirt);
		return (NULL);
	}
	
	/* LIGHT */
	
	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
	minirt->lights[0]->position = return_tuple(-10, 10, -10, POINT);
	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	
	minirt->lights[1] = ft_calloc(1, sizeof(t_light));
	minirt->lights[1]->position = return_tuple(0, 3, 0, POINT);
	minirt->lights[1]->intensity.colors = return_tuple(1, 0, 0, COLOR);

	//minirt->object_count = 1;
	//minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));
	//t_sphere *test = create_sphere(0, 0, 0, 1, create_default_material());
	//minirt->shapes[0] = create_shape(SPHERE, test);

	/* LIGHT */
	
	//t_sphere *middle = create_sphere(0, 0, 0, 0.5, create_default_material());
	//middle->transform = translation_mat(-1, 0, 0);
	//middle->material->color.colors = return_tuple(0.1, 1, 0.5, COLOR);
	//middle->material->diffuse = 0.7;
	//middle->material->specular = 0.3;
	//minirt->shapes[0] = create_shape(SPHERE, middle);
	//transform_shape(minirt, 0, translate, 0, return_tuple_pointer(-1, 0, 0, POINT));

	//t_sphere *last = create_sphere(0, 0, 0, 0.5, create_default_material());
	//last->material->color.colors = return_tuple(0, 1, 0, COLOR);
	//last->material->specular = 1;
	//minirt->shapes[2] = create_shape(SPHERE, last);
	//transform_shape(minirt, 2, translate, 0, return_tuple_pointer(0, 0, 0, POINT));
	
	//t_plane *plane = ft_calloc(1, sizeof(t_plane));
	//minirt->shapes[3] = create_shape(PLANE, plane);
	//transform_shape(minirt, 3, rotate_x, DEG_RAD(30), NULL);
	//transform_shape(minirt, 3, translate, 0 , return_tuple_pointer(0, -0.7, 0, POINT));

	//t_cylinder *cylinder = create_cylinder(return_tuple(0, 0, 0, POINT));
	//cylinder->is_closed = true;
	//cylinder->minimum = -0.5;
	//cylinder->maximum = 0.3;
	//cylinder->material->color.colors = return_tuple(1, 0, 0, COLOR);
	//minirt->shapes[1] = create_shape(CYLINDER, cylinder);
	//transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0.5, 0, 0, POINT));
	
	
	/* SCENE */

	minirt->object_count = 1;
	minirt->shapes = ft_calloc(1, sizeof(t_shape *));
	
	t_sphere *floor = create_sphere(0, 0, 0, 1, create_default_material());
	minirt->shapes[0] = create_shape(SPHERE, floor);
	floor->material->color.colors = return_tuple(1, 0.9, 0.9, COLOR);
	floor->material->specular = 0.1;
	transform_shape(minirt, 0, scale, 0, return_tuple_pointer(1.5, 0.5, 1.5, POINT));
	transform_shape(minirt, 0, rotate_z, DEG_RAD(30), NULL);
	
	//t_sphere *floor = create_sphere(0, 0, 0, 1, create_default_material());
	//minirt->shapes[0] = create_shape(SPHERE, floor);
	//floor->material->color.colors = return_tuple(1, 0.9, 0.9, COLOR);
	//floor->material->specular = 0;
	//transform_shape(minirt, 0, scale, 0, return_tuple_pointer(10, 0.01, 10, POINT));
	
	//t_sphere *left_wall = create_sphere(0, 0, 0, 1, create_default_material());
	//minirt->shapes[0] = create_shape(SPHERE, left_wall);
	//transform_shape(minirt, 0, scale, 0, return_tuple_pointer(10, 0.01, 10, POINT));
	//transform_shape(minirt, 0, rotate_x, PI / 2, NULL);
	//transform_shape(minirt, 0, rotate_y, -PI / 4, NULL);
	//transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0, 0, 5, POINT));
	
	//t_sphere *right_wall = create_sphere(0, 0, 0, 1, create_default_material());
	//minirt->shapes[2] = create_shape(SPHERE, right_wall);
	//transform_shape(minirt, 2, scale, 0, return_tuple_pointer(10, 0.01, 10, POINT));
	//transform_shape(minirt, 2, rotate_x, PI / 2, NULL);
	//transform_shape(minirt, 2, rotate_y, PI / 4, NULL);
	//transform_shape(minirt, 2, translate, 0, return_tuple_pointer(0, 0, 5, POINT));
	
	//t_sphere *middle = create_sphere(0, 0, 0, 1, create_default_material());
	//middle->material->color.colors = return_tuple(0.1, 1, 0.5, COLOR);
	//middle->material->diffuse = 0.7;
	//middle->material->specular = 0.3;
	//minirt->shapes[3] = create_shape(SPHERE, middle);
	//transform_shape(minirt, 3, translate, 0, return_tuple_pointer(-0.5, 1, 0.5, POINT));
	
	//t_sphere *right = create_sphere(0, 0, 0, 1, create_default_material());
	//right->material->color.colors = return_tuple(0.5, 1, 0.1, COLOR);
	//right->material->diffuse = 0.7;
	//right->material->specular = 0.3;
	//minirt->shapes[4] = create_shape(SPHERE, right);
	//transform_shape(minirt, 4, scale, 0, return_tuple_pointer(0.8, 0.8, 0.8, POINT));
	//transform_shape(minirt, 4, translate, 0, return_tuple_pointer(1.5, 0.5, -0.5, POINT));
	
	//t_sphere *left = create_sphere(0, 0, 0, 1, create_default_material());
	//left->material->color.colors = return_tuple(1, 0.8, 0.1, COLOR);
	//left->material->diffuse = 0.7;
	//left->material->specular = 0.3;
	//minirt->shapes[5] = create_shape(SPHERE, left);
	//transform_shape(minirt, 5, translate, 0, return_tuple_pointer(-1.5, 1, -0.75, POINT));
	

	minirt->mlx = mlx;
	(void)temp;
	return (minirt);
}

//t_minirt	* init_default(t_mlx *mlx)
//{
//	t_minirt	*minirt;
//	t_4dmat		temp;
	
//	minirt = ft_calloc(1, sizeof(t_minirt));
//	if (!minirt)
//		return (NULL);
//	minirt->spheres = ft_calloc(2, sizeof(t_sphere *));
//	if (!minirt->spheres)
//	{
//		free(minirt);
//		return (NULL);
//	}
//	minirt->light_count = 1;
//	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
//	if (!minirt->lights)
//	{
//		free(minirt->spheres);
//		free(minirt);
//		return (NULL);
//	}
	
//	/* LIGHT */
	
//	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
//	minirt->lights[0]->position = return_tuple(0, 0, -10, POINT);
//	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	
//	minirt->object_count = 2;
//	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));

//	t_sphere *sphere_one = create_sphere(0, 0, 0, 1, create_default_material());
//	minirt->shapes[0] = create_shape(SPHERE, sphere_one);
//	transform_shape(minirt, 0, translate, 0, return_tuple_pointer(0.2, 0, 0, POINT));

//	t_sphere *sphere_two = create_sphere(0, 0, 0, 1, create_default_material());
//	minirt->shapes[1] = create_shape(SPHERE, sphere_two);
//	transform_shape(minirt, 1, scale, 0, return_tuple_pointer(3, 3, 3, POINT));
//	transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0, 0, 2, POINT));

//	minirt->mlx = mlx;
//	(void)temp;
//	return (minirt);
//}
