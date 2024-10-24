/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/24 21:38:22 by pipolint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_shapes(t_minirt *minirt);

void	print_4d_points(double points[4][4])
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

int		get_key_pressed(int keycode, t_mlx *mlx, t_minirt *m)
{
	//if (keycode == PLUS)
	//	transform_sphere(sphere, scale, return_tuple(1, 2, 1, POINT));
	if (keycode == W)
	{
		printf("w\n");
		//m->from = return_tuple(m->from.x, m->from.y + 2, m->from.z, POINT);		
		m->cam->view_matrix = view_transform(&m->to, &m->from, &m->up);
		render(mlx, m->cam, m);
	}
	else if (keycode == ESC)
		exit(1);
	(void)mlx;
	(void)m;
	return (0);
}

//int main(void)
//{
//	t_mlx		mlx;
//	t_minirt 	*m;
//	t_4dmat		temp;

//	init_mlx(&mlx);
//	m = init_default(&mlx);
//	//mlx_hook(mlx.win, 2, 0, get_key_pressed, m);
//	m->cam = return_camera_ptr(WIDTH, HEIGHT, DEG_RAD(60), NULL);
//	m->from = return_tuple(0, 0, -2, POINT);
//	//from = return_tuple(1, 0, 2, POINT);
//	m->to = return_tuple(0, 0, 0, POINT);
//	m->up = return_tuple(0, 1, 0, VECTOR);
//	m->cam->view_matrix = view_transform(&m->to, &m->from, &m->up);
//	//camera.view_matrix = view_transform(&m->to, &m->from, &m->up);
//	//temp = translation_mat(0, 0, -1);
//	//camera.view_matrix = mat4d_mult_fast(&temp, camera.view_matrix);
//	//temp = y_rotation_mat(DEG_RAD(10));
//	//camera.view_matrix = mat4d_mult_fast(&temp, camera.view_matrix);
//	//mlx_loop_hook(&mlx.mlx, render, m);
//	render(&mlx, m->cam, m);
//	(void)temp;
//	mlx_loop(&mlx.mlx);
//}

int main(void)
{
	t_minirt 	*m;
	t_mlx		mlx;
	t_4dmat		temp;

	init_mlx(&mlx);
	m = init_default(&mlx);
	m->cam = return_camera_ptr(WIDTH, HEIGHT, PI / 3, NULL);
	m->from = return_tuple(0, 1.5, -5, POINT);
	m->to = return_tuple(0, 1, 0, POINT);
	m->up = return_tuple(0, 1, 0, VECTOR);
	m->cam->view_matrix = view_transform(&m->to, &m->from, &m->up);
	//render(&mlx, m->cam, m);
	threaded_render(&mlx, m, m->cam);
	(void)temp;
	mlx_loop(&mlx.mlx);
}
