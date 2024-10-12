/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/12 17:45:34 by pipolint         ###   ########.fr       */
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
	
	minirt->lights[1] = ft_calloc(1, sizeof(t_light));
	if (!minirt->lights[1])
		return (NULL);
	minirt->lights[1]->intensity.colors = return_tuple(0.2, 0.2, 0.2, COLOR);
	minirt->lights[1]->position = return_tuple(0, -5, -5, POINT);
	/* LIGHT */
	
	minirt->object_count = 2;
	
	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));
	
	///* FIRST SPHERE */
	//minirt->spheres[0] = ft_calloc(1, sizeof(t_sphere));
	//if (!minirt->spheres[0])
	//	return (NULL);
	//t_color	c;
	//c.colors = return_tuple(0.8, 1, 0.6, COLOR);
	//minirt->spheres[0]->material = create_material(c, 0.7, 0.1, 0.2, 200);
	//minirt->spheres[0]->radius = 0.5;
	//minirt->spheres[0]->center = return_tuple(0, 0, 0, POINT);
	//minirt->spheres[0]->transform = identity();

	//if (!minirt->spheres[0])
	//	return (NULL);
	//minirt->spheres[0]->material = create_material(c, 0.7, 0.1, 0.2, 200);
	//minirt->spheres[0]->radius = 0.5;
	//minirt->spheres[0]->center = return_tuple(0, 0, 0, POINT);
	//minirt->spheres[0]->transform = identity();
	/* FIRST SPHERE */
	
	///* SECOND SPHERE */
	//minirt->spheres[1] = create_sphere(0, 0, 0, create_default_material());
	//minirt->spheres[1]->radius = 1;
	//minirt->spheres[1]->center = return_tuple(0, 0, 0, POINT);
	//transform_sphere(minirt->spheres[1], scale, return_tuple(0.5, 0.5, 0.5, POINT));
	///* SECOND SPHERE */

	///* PLANE */
	//minirt->plane = ft_calloc(1, sizeof(t_plane));
	//minirt->plane->material = create_default_material();
	//minirt->plane->point = return_tuple(0, 0, 0, POINT);
	//minirt->plane->transform = identity();

	minirt->shapes[0] = ft_calloc(1, sizeof(t_shape));
	t_mater*	default_material = create_default_material();
	t_sphere *sphere = create_sphere(0, 0, 0, default_material);
	sphere->material->color.colors = return_tuple(0.1, 0.2, 0.6, COLOR);
	
	sphere->radius = 0.5;
	sphere->center = return_tuple(0, 0, 0, POINT);
	sphere->transform = identity();
	minirt->shapes[0]->shape = sphere;
	minirt->shapes[0]->type = SPHERE;

	t_plane *plane = ft_calloc(1, sizeof(t_plane));
	plane->material = create_default_material();
	plane->transform = identity();
	plane->point = return_tuple(0, 0, 0, POINT);
	plane->transform = x_rotation_mat(DEG_RAD(45));
	minirt->shapes[1] = ft_calloc(1, sizeof(t_shape));
	minirt->shapes[1]->shape = plane;
	minirt->shapes[1]->type = PLANE;

	minirt->mlx = mlx;
	minirt->light_count = 2;
	return (minirt);
}
