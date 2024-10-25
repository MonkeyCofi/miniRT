/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/25 18:49:07 by pipolint         ###   ########.fr       */
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

t_minirt	* init_default(t_mlx *mlx)
{
	t_minirt	*minirt;
	t_4dmat		temp;
	
	minirt = ft_calloc(1, sizeof(t_minirt));
	if (!minirt)
		return (NULL);
	minirt->light_count = 2;
	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
	if (!minirt->lights)
	{
		free(minirt);
		return (NULL);
	}
	
	/* LIGHT */
	
	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
	minirt->lights[0]->position = return_tuple(0, 1, -2, POINT);
	minirt->lights[0]->intensity.colors = return_tuple(1, 1, 1, COLOR);
	
	minirt->lights[1] = ft_calloc(1, sizeof(t_light));
	minirt->lights[1]->position = return_tuple(2, 0, 0, POINT);
	minirt->lights[1]->intensity.colors = return_tuple(1, 0, 1, COLOR);
	
	minirt->object_count = 7;
	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));

	t_plane *wall = create_plane();
	minirt->shapes[0] = create_shape(PLANE, wall);
	transform_shape(minirt, 0, translate, 0, return_tuple_pointer(0, 0, 2.5, POINT));
	transform_shape(minirt, 0, rotate_x, DEG_RAD(90), NULL);
	
	t_plane	*floor = create_plane();
	minirt->shapes[1] = create_shape(PLANE, floor);
	transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0, -1, 0, POINT));
	transform_shape(minirt, 1, rotate_x, DEG_RAD(0), NULL);
	
	t_cone	*cone = create_cone();
	cone->maximum = 0.5;
	cone->minimum = -0.5;
	minirt->shapes[2] = create_shape(CONE, cone);
	transform_shape(minirt, 2, rotate_x, -DEG_RAD(40), NULL);
	transform_shape(minirt, 2, translate, 0, return_tuple_pointer(3, 0, 0, POINT));
	
	t_cylinder	*cylinder = create_cylinder(return_point(0, 0, 0));
	cylinder->maximum = 1;
	cylinder->minimum = -1;
	//cylinder->is_closed = true;
	minirt->shapes[3] = create_shape(CYLINDER, cylinder);
	transform_shape(minirt, 3, rotate_x, -DEG_RAD(80), NULL);
	transform_shape(minirt, 3, translate, 0, return_tuple_pointer(-3, 0.5, 0, POINT));
	
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
	minirt->shapes[4] = create_shape(SPHERE, sphere);
	transform_shape(minirt, 4, translate, 0, return_tuple_pointer(0, 0, 0.9, POINT));
	
	t_sphere *sphere_two = create_sphere(0, 0, 0, 0.5, create_default_material());
	sphere_two->material->color = return_color(1, 0, 0);
	minirt->shapes[5] = create_shape(SPHERE, sphere_two);
	transform_shape(minirt, 5, translate, 0, return_tuple_pointer(3, 2, 0, POINT));
	transform_shape(minirt, 5, scale, 0, return_tuple_pointer(1, 2, 1, POINT));

	t_sphere *new_sphere = create_sphere(0, 0, 0, 1, create_default_material());
	new_sphere->material->color = return_color(0.7, 0.5, 0.3);
	minirt->shapes[6] = create_shape(SPHERE, new_sphere);
	transform_shape(minirt, 6, translate, 0, return_tuple_pointer(0, 3, 0, POINT));

	minirt->mlx = mlx;
	(void)temp;
	return (minirt);
}
