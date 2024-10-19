/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/19 20:36:57 by pipolint         ###   ########.fr       */
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
	minirt->light_count = 5;
	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
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
	minirt->lights[0]->position = return_tuple(0, 0.4, 0, POINT);
	
	minirt->lights[1] = ft_calloc(1, sizeof(t_light));
	if (!minirt->lights[1])
		return (NULL);
	minirt->lights[1]->intensity.colors = return_tuple(0.5, 0, 1, COLOR);
	minirt->lights[1]->position = return_tuple(0, -0.4, 0, POINT);
	
	minirt->lights[2] = ft_calloc(1, sizeof(t_light));
	if (!minirt->lights[2])
		return (NULL);
	minirt->lights[2]->intensity.colors = return_tuple(0, 0.7, 1, COLOR);
	minirt->lights[2]->position = return_tuple(0.8, 0, 0, POINT);
	
	minirt->lights[3] = ft_calloc(1, sizeof(t_light));
	if (!minirt->lights[3])
		return (NULL);
	minirt->lights[3]->intensity.colors = return_tuple(1, 1, 0, COLOR);
	minirt->lights[3]->position = return_tuple(-1, 0, 0, POINT);
	
	minirt->lights[4] = ft_calloc(1, sizeof(t_light));
	if (!minirt->lights[4])
		return (NULL);
	minirt->lights[4]->intensity.colors = return_tuple(1, 0, 0, COLOR);
	minirt->lights[4]->position = return_tuple(0, 0, -0.3, POINT);
	
	//minirt->lights[2] = ft_calloc(1, sizeof(t_light));
	//if (!minirt->lights[2])
	//	return (NULL);
	//minirt->lights[2]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	//minirt->lights[2]->position = return_tuple(0, 0, 0.99, POINT);

	/* LIGHT */
	
	minirt->object_count = 1;
	
	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));
	
	t_cylinder *cylinder = create_cylinder(return_tuple(0, 0, 0, VECTOR));
	cylinder->material->color.colors = return_tuple(1, 1, 1, COLOR);
	cylinder->radius = 0.4;
	cylinder->minimum = -0.1;
	cylinder->maximum = 1;
	cylinder->transform = x_rotation_mat(DEG_RAD(30));
	cylinder->is_closed = true;
	minirt->shapes[0] = create_shape(CYLINDER, cylinder);
	if (transform_shape(minirt, 0, rotate_x, DEG_RAD(30), NULL) == error)
	{
		write(2, "Malloc error\n", 14);
		return (NULL);
	};

	//t_sphere *sphere = create_sphere(0, 0, 0, create_default_material());
	//sphere->transform = translation_mat(0, 0, 1);
	//sphere->radius = 0.3;
	//sphere->material->color.colors = return_tuple(0.5, 0.3, 0.1, COLOR);
	//minirt->shapes[1] = ft_calloc(1, sizeof(t_shape));
	//minirt->shapes[1]->shape = sphere;
	//minirt->shapes[1]->type = SPHERE;
	//(void)temp;
	
	//t_sphere *sphere_two = create_sphere(0, 0, 0, create_default_material());
	//sphere_two->radius = 0.4;
	//sphere_two->transform = identity();
	//minirt->shapes[0] = create_shape(SPHERE, sphere_two);
	
	//t_plane *plane_two = ft_calloc(1, sizeof(t_plane));
	//plane_two->material = create_default_material();
	//plane_two->material->ambient = 0.2;
	//plane_two->transform = x_rotation_mat(PI / 2);
	//temp = translation_mat(0, 0, 0.1);
	//plane_two->transform = mat4d_mult_fast_static(&temp, &plane_two->transform);
	//minirt->shapes[1] = create_shape(PLANE, plane_two);
	
	minirt->mlx = mlx;
	(void)temp;
	return (minirt);
}
