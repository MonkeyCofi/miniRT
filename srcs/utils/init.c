/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaarij <ahaarij@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:17:00 by pipolint          #+#    #+#             */
/*   Updated: 2024/11/04 09:05:48 by ahaarij          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_minirt *init_minirtaarij(t_minirt *m)
{
	m->cam = ft_calloc(1, sizeof(t_camera));
	m->shapes = ft_calloc(1, (sizeof(t_shape)));
	m->ambient = ft_calloc(1, sizeof(t_ambient));
	m->lights = ft_calloc(1, (sizeof(t_light)));
	m->up = return_tuple(0, 1, 0, VECTOR);
	m->ambient->flag = 0;
	m->ambient->ratio = 0;
	m->cam->flag = 0;
	m->object_count = 0;
	m->light_count = 0;
	
	return (m);
}

t_minirt *init_sphere(t_minirt *m, int *i)
{
	t_sphere *sphere = create_sphere(0, 0, 0, m->shapes[*i]->r);
	t_tuple coords = m->shapes[*i]->coords;
	t_mater *material = m->shapes[*i]->material;
	t_tuple orientation = m->shapes[*i]->orientation;
	m->shapes[*i] = create_shape(SPHERE, sphere);
	m->shapes[*i]->material = material;
	if(m->shapes[*i]->material->is_patterned == true){
		create_pattern(material->pattern.color_one,
					m->shapes[*i]->material->pattern.color_two,
					10, &m->shapes[*i]->material->pattern);
	}
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, translate, 0, &coords);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_x, DEG_RAD(orientation.x), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_y, DEG_RAD(orientation.y), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_z, DEG_RAD(orientation.z), NULL);
	*i += 1;
	return (m);
}

t_minirt *init_plane(t_minirt *m, int *i)
{
	t_plane *plane = create_plane();
	t_tuple coords = m->shapes[*i]->coords;
	t_mater *material = m->shapes[*i]->material;
	t_tuple orientation = m->shapes[*i]->orientation;
	m->shapes[*i] = create_shape(PLANE, plane);
	m->shapes[*i]->material = material;
	if(m->shapes[*i]->material->is_patterned == true){
		create_pattern(material->pattern.color_one,
					m->shapes[*i]->material->pattern.color_two,
					10, &m->shapes[*i]->material->pattern);
	}
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, translate, 0, &coords);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_x, DEG_RAD(orientation.x), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_y, DEG_RAD(orientation.y), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_z, DEG_RAD(orientation.z), NULL);
	*i += 1;
	return(m);
}

t_minirt *init_cylinder(t_minirt *m, int *i)
{
	t_cylinder *cylinder = create_cylinder(return_point(0, 0, 0));
	t_tuple coords = m->shapes[*i]->coords;
	t_tuple orientation = m->shapes[*i]->orientation;
	t_mater *material = m->shapes[*i]->material;
	cylinder->maximum = m->shapes[*i]->h;
	cylinder->minimum = 0;
	cylinder->radius = m->shapes[*i]->r;
	cylinder->is_closed = 1;
	m->shapes[*i] = create_shape(CYLINDER, cylinder);
	m->shapes[*i]->material = material;
	if(m->shapes[*i]->material->is_patterned == true){
		create_pattern(material->pattern.color_one,
					m->shapes[*i]->material->pattern.color_two,
					10, &m->shapes[*i]->material->pattern);
	}
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, translate, 0, &coords);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_x, DEG_RAD(orientation.x), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_y, DEG_RAD(orientation.y), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_z, DEG_RAD(orientation.z), NULL);
	*i += 1;
	return (m);
}

t_minirt *init_cone(t_minirt *m, int *i)
{
	t_cone *cone = create_cone();
	t_tuple coords = m->shapes[*i]->coords;
	t_tuple orientation = m->shapes[*i]->orientation;
	t_mater *material = m->shapes[*i]->material;
	cone->minimum = -m->shapes[*i]->h;
	cone->maximum = m->shapes[*i]->h;
	cone->is_closed = true;
	m->shapes[*i] = create_shape(CONE, cone);
	m->shapes[*i]->material = material;
	if(m->shapes[*i]->material->is_patterned == true){
		create_pattern(material->pattern.color_one,
					m->shapes[*i]->material->pattern.color_two,
					10, &m->shapes[*i]->material->pattern);
	}
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, translate, 0, &coords);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_x, DEG_RAD(orientation.x), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_y, DEG_RAD(orientation.y), NULL);
	m->shapes[*i]->transform = identity();
	transform_shape(m, *i, rotate_z, DEG_RAD(orientation.z), NULL);
	*i += 1;
	return (m);
}

//t_minirt	* init_default(t_mlx *mlx)
//{
//	t_minirt	*minirt;
//	t_4dmat		temp;
	
//	minirt = ft_calloc(1, sizeof(t_minirt));
//	if (!minirt)
//		return (NULL);
//	minirt->light_count = 3;
//	minirt->lights = ft_calloc(minirt->light_count, sizeof(t_light *));
//	if (!minirt->lights)
//	{
//		free(minirt);
//		return (NULL);
//	}
	
//	/* LIGHT */
	
//	minirt->lights[0] = ft_calloc(1, sizeof(t_light));
//	minirt->lights[0]->position = return_tuple(0, 1, -2, POINT);
//	minirt->lights[0]->intensity.colors = return_tuple(1, 0, 0.7, COLOR);
//	minirt->lights[0]->brightness = 1;
	
//	minirt->lights[1] = ft_calloc(1, sizeof(t_light));
//	minirt->lights[1]->position = return_tuple(2, 0, 0, POINT);
//	//minirt->lights[1]->intensity.colors = return_tuple(1, 0, 1, COLOR);
//	minirt->lights[1]->intensity.colors = return_tuple(0, 0.4, 0.4, COLOR);
//	minirt->lights[1]->brightness = 1;

//	minirt->lights[2] = ft_calloc(1, sizeof(t_light));
//	minirt->lights[2]->position = return_tuple(-6, 0.5, 0, POINT);
//	minirt->lights[2]->intensity.colors = return_tuple(0, 0, 1, COLOR);
//	minirt->lights[2]->brightness = 1;
	
//	minirt->object_count = 10;
//	minirt->shapes = ft_calloc(minirt->object_count, sizeof(t_shape *));

//	t_plane *back_wall = create_plane();
//	minirt->shapes[0] = create_shape(PLANE, back_wall);
//	minirt->shapes[0]->material->is_patterned = true;
//	minirt->shapes[0]->material->pattern = create_pattern(return_color(0, 0, 0), return_color(1, 1, 1), 1);
//	transform_shape(minirt, 0, rotate_x, DEG_RAD(90), NULL);
//	transform_shape(minirt, 0, translate, 0, return_tuple_pointer(0, 0, 10, POINT));
	
//	t_plane	*floor = create_plane();
//	minirt->shapes[1] = create_shape(PLANE, floor);
//	transform_shape(minirt, 1, translate, 0, return_tuple_pointer(0, -1, 0, POINT));
//	transform_shape(minirt, 1, rotate_x, DEG_RAD(0), NULL);
	
//	t_cone	*cone = create_cone();
//	cone->maximum = 1;
//	cone->minimum = 0;
//	cone->is_closed = true;
//	minirt->shapes[2] = create_shape(CONE, cone);
//	minirt->shapes[2]->material->color = return_color(1, 0 ,0);
//	transform_shape(minirt, 2, translate, 0, return_tuple_pointer(2, 1, 0, POINT));
//	//transform_shape(minirt, 2, rotate_x, 0, NULL);
//	//transform_shape(minirt, 2, rotate_x, DEG_RAD(90), NULL);
	
//	t_cylinder	*cylinder = create_cylinder(return_point(0, 0, 0));
//	cylinder->minimum = -1;
//	cylinder->maximum = 2;
//	cylinder->is_closed = 1;
//	minirt->shapes[3] = create_shape(CYLINDER, cylinder);
//	minirt->shapes[3]->material->is_patterned = true;
//	minirt->shapes[3]->material->pattern = create_pattern(return_color(1, 0, 0), return_color(0, 1, 0), 12);
//	transform_shape(minirt, 3, translate, 0, return_tuple_pointer(-3, 0.5, 0, POINT));
//	transform_shape(minirt, 3, rotate_y, DEG_RAD(80), NULL);
//	transform_shape(minirt, 3, rotate_x, -DEG_RAD(80), NULL);
	
//	t_sphere *sphere = create_sphere(0, 0, 0, 1, create_default_material());
//	minirt->shapes[4] = create_shape(SPHERE, sphere);
//	minirt->shapes[4]->material->is_patterned = true;
//	//minirt->shapes[4]->material->pattern = stripe(return_color(0.3, 1, 0.5), return_color(0, 1, 1), 5);
//	//minirt->shapes[4]->material->pattern = create_pattern(return_color(0, 0, 0), return_color(1, 1, 1), 10);
//	transform_shape(minirt, 4, translate, 0, return_tuple_pointer(0, 0, 0.9, POINT));
	
//	t_sphere *pill = create_sphere(0, 0, 0, 0.5, create_default_material());
//	minirt->shapes[5] = create_shape(SPHERE, pill);
//	minirt->shapes[5]->material->is_patterned = true;
//	minirt->shapes[5]->material->pattern = create_pattern(return_color(0, 1, 1), return_color(0, 0, 0), 10);
//	transform_shape(minirt, 5, translate, 0, return_tuple_pointer(3, 2, 0, POINT));
//	transform_shape(minirt, 5, scale, 0, return_tuple_pointer(1, 2, 1, POINT));

//	t_sphere *new_sphere = create_sphere(0, 0, 0, 1, create_default_material());
//	new_sphere->material->color = return_color(0.7, 0.5, 0.3);
//	minirt->shapes[6] = create_shape(SPHERE, new_sphere);
//	transform_shape(minirt, 6, translate, 0, return_tuple_pointer(0, 3, 0, POINT));
	
//	t_plane	*left_wall = create_plane();
//	minirt->shapes[7] = create_shape(PLANE, left_wall);
//	minirt->shapes[7]->material->color = return_color(0.3, 0, 0);
//	minirt->shapes[7]->material->specular = 0;
//	transform_shape(minirt, 7, translate, 0, return_tuple_pointer(-10, 0, 0, POINT));
//	transform_shape(minirt, 7, rotate_z, DEG_RAD(90), NULL);

//	t_plane	*right_wall = create_plane();
//	minirt->shapes[8] = create_shape(PLANE, right_wall);
//	minirt->shapes[8]->material->color = return_color(0, 1, 0);
//	transform_shape(minirt, 8, translate, 0, return_tuple_pointer(10, 0, 0, POINT));
//	transform_shape(minirt, 8, rotate_z, DEG_RAD(90), NULL);

//	t_plane	*ceiling = create_plane();
//	minirt->shapes[9] = create_shape(PLANE, ceiling);
//	minirt->shapes[9]->material->color = return_color(0, 0.5, 0.5);
//	transform_shape(minirt, 9, translate, 0, return_tuple_pointer(0, 8, 0, POINT));
//	transform_shape(minirt, 9, rotate_x, DEG_RAD(0), NULL);

//	minirt->mlx = mlx;
//	(void)temp;
//	return (minirt);
//}
