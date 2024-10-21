/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/21 21:28:27 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt);

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

int	get_key_pressed(int keycode, t_mlx *mlx, t_sphere *sphere)
{
	if (keycode == PLUS)
		transform_sphere(sphere, scale, return_tuple(1, 2, 1, POINT));
	else if (keycode == ESC)
		exit(1);
	(void)mlx;
	return (0);
}

int main(void)
{
	t_mlx		mlx;
	t_minirt 	*m;
	t_camera	camera;
	t_tuple		from;
	t_tuple		to;
	t_tuple		up;
	t_4dmat		temp;

	init_mlx(&mlx);
	m = init_default(&mlx);
	camera = return_camera(WIDTH, HEIGHT, DEG_RAD(60), NULL);
	from = return_tuple(0, 1.5, -5, POINT);
	to = return_tuple(0, 1, 0, POINT);
	up = return_tuple(0, 1, 0, VECTOR);
	camera.view_matrix = view_transform(&to, &from, &up);
	render(&mlx, &camera, m);
	(void)temp;
	mlx_loop(&mlx.mlx);
}

//int main(void)
//{
//	t_mlx 		mlx;
//	t_minirt	*world;
//	//t_camera	camera;
//	t_sphere 	*sphere;

//	init_mlx(&mlx);
//	world = init_default(&mlx);
//	sphere = create_sphere(0, 0, 0, 1, create_default_material());
//	world->shapes = ft_calloc(1, sizeof(t_shape *));
//	world->shapes[0] = create_shape(SPHERE, sphere);
//	world->shapes[0]->normal = normal_sphere;
//	world->shapes[0]->intersect = sphere_hit;
//	transform_shape(world, 0, scale, 0, return_tuple_pointer(1, 0.5, 1, POINT));
//	transform_shape(world, 0, rotate_z, PI / 5, NULL);
//	t_tuple *normal = normal_sphere(world->shapes[0], return_tuple(0, 1.70711, -0.70711, POINT));
//	print_tuple_points(normal);
//}