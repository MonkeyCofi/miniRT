/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/25 01:35:48 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

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

//t_minirt	* init_default(t_mlx *mlx)
//{
//	t_minirt	*minirt;
//	t_4dmat		temp;
	
//	minirt = ft_calloc(1, sizeof(t_minirt));
//	if (!minirt)
//		return (NULL);
//	minirt->light_count = 2;
//	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
//	if (!minirt->lights)
//	{
//		free(minirt);
//		return (NULL);
//	}
	
//	/* LIGHT */
	
//	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
//	minirt->lights[0]->position = return_tuple(-10, 10, -10, POINT);
//	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	
//	minirt->lights[1] = ft_calloc(1, sizeof(t_light));
//	minirt->lights[1]->position = return_tuple(0, 0, -1, POINT);
//	minirt->lights[1]->intensity.colors = return_tuple(1, 0, 0, COLOR);
	
//	/* LIGHT */
	
//	/* SCENE */

//	minirt->object_count = 6;
//	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));
	
//	t_plane *floor = create_plane();
//	minirt->shapes[0] = create_shape(PLANE, floor);

//	t_plane *left_wall = create_plane();
//	minirt->shapes[1] = create_shape(PLANE, left_wall);
//	transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0, 0, 15, POINT));
//	transform_shape(minirt, 1, rotate_x, DEG_RAD(120), NULL);
	
//	t_plane *right_wall = create_plane();
//	minirt->shapes[2] = create_shape(PLANE, right_wall);
//	transform_shape(minirt, 2, translate, 0, return_tuple_pointer(0, 0, 15, POINT));
//	transform_shape(minirt, 2, rotate_y, -DEG_RAD(80), NULL);
//	transform_shape(minirt, 2, rotate_x, DEG_RAD(100), NULL);

//	t_sphere *middle = create_sphere(0, 0, 0, 1, create_default_material());
//	middle->material->color = return_tuple(0.1, 1, 0.5, COLOR);
//	middle->material->diffuse = 0.7;
//	middle->material->specular = 0.3;
//	minirt->shapes[3] = create_shape(SPHERE, middle);
//	transform_shape(minirt, 3, translate, 0, return_tuple_pointer(-0.5, 0.9, -1, POINT));
//	transform_shape(minirt, 3, scale, 0, return_tuple_pointer(1, 0.3, 1, POINT));
	
//	t_sphere *right = create_sphere(0, 0, 0, 1, create_default_material());
//	right->material->color = return_tuple(0.5, 1, 0.1, COLOR);
//	right->material->diffuse = 0.7;
//	right->material->specular = 0.3;
//	minirt->shapes[4] = create_shape(SPHERE, right);
//	transform_shape(minirt, 4, scale, 0, return_tuple_pointer(0.5, 0.5, 0.5, POINT));
//	transform_shape(minirt, 4, translate, 0, return_tuple_pointer(2, 1, -0.5, POINT));
	
//	t_sphere *left = create_sphere(0, 0, 0, 1, create_default_material());
//	left->material->color = return_tuple(1, 0.8, 0.1, COLOR);
//	left->material->diffuse = 0.7;
//	left->material->specular = 0.3;
//	minirt->shapes[5] = create_shape(SPHERE, left);
//	transform_shape(minirt, 5, translate, 0, return_tuple_pointer(-1.5, 0.33, -0.75, POINT));
//	transform_shape(minirt, 5, scale, 0, return_tuple_pointer(0.33, 0.33, 0.33, POINT));
	
//	//t_cylinder *cylinder = create_cylinder(return_point(0, 0, 0));
//	//minirt->shapes[6] = create_shape(CYLINDER, cylinder);
//	//cylinder->is_closed = true;
//	//cylinder->minimum = 0;
//	//cylinder->maximum = 1;
//	//transform_shape(minirt, 6, translate, 0, return_tuple_pointer(0, 2, 0, POINT));
//	//transform_shape(minirt, 6, rotate_x, DEG_RAD(50), NULL);
//	//transform_shape(minirt, 6, rotate_y, DEG_RAD(30), NULL);

//	minirt->mlx = mlx;
//	(void)temp;
//	return (minirt);
//}

t_minirt	* init_default(t_mlx *mlx)
{
	t_minirt	*minirt;
	t_4dmat		temp;
	
	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		return (NULL);
	minirt->light_count = 1;
	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
	if (!minirt->lights)
	{
		free(minirt);
		return (NULL);
	}
	
	/* LIGHT */
	
	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
	minirt->lights[0]->position = return_tuple(0, 0, -2, POINT);
	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	
	minirt->object_count = 2;
	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));

	t_plane *wall = create_plane();
	minirt->shapes[0] = create_shape(PLANE, wall);
	transform_shape(minirt, 0, translate, 0, return_tuple_pointer(0, 0, 1, POINT));
	transform_shape(minirt, 0, rotate_x, DEG_RAD(90), NULL);
	
	// t_cylinder *cylinder = create_cylinder(return_point(0, 0, 0));
	// cylinder->material->color = return_tuple(0, 1, 0, COLOR);
	// cylinder->minimum = 0;
	// cylinder->maximum = 1;
	// cylinder->is_closed = true;
	// minirt->shapes[1] = create_shape(CYLINDER, cylinder);
	// transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0, 2, 0, POINT));
	// transform_shape(minirt, 1, rotate_x, DEG_RAD(50), NULL);
	// transform_shape(minirt, 1, rotate_y, DEG_RAD(30), NULL);
	
	t_sphere *sphere = create_sphere(0, 0, 0, 1, create_default_material());
	minirt->shapes[1] = create_shape(SPHERE, sphere);
	transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0, 1.5, -1, POINT));

	minirt->mlx = mlx;
	(void)temp;
	return (minirt);
}
