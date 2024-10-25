/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pipolint <pipolint@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 10:27:03 by pipolint          #+#    #+#             */
/*   Updated: 2024/10/25 18:33:27 by pipolint         ###   ########.fr       */
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

// int		get_key_pressed(int keycode, t_hook_params hooks)
// {
// 	t_minirt *m = hooks.m;
// 	m->cam->view_matrix = hooks.m->cam->view_matrix;
// 	t_mlx *mlx = hooks.mlx;
// 	//if (keycode == PLUS)
// 	//	transform_sphere(sphere, scale, return_tuple(1, 2, 1, POINT));
// 	if (keycode == W)
// 	{
// 		printf("W pressed. m: %p, m->cam: %p\n", m, m->cam);
// 		print_4dmatrix(m->cam->view_matrix);
// 		// m->from = return_tuple(m->from.x, m->from.y + 2, m->from.z, POINT);	
// 		m->cam->view_matrix = view_transform(&m->to, &m->from, &m->up);
// 		render(mlx, m->cam, m);
// 	}
// 	else if (keycode == ESC)
// 		exit(1);
// 	(void)mlx;
// 	(void)m;
// 	return (0);
// }

int	closert(t_minirt *m)
{
	// int i;
	// if(m->cam)
		// free cam func
	// if (m->lights)
	// 	free lights func
	// if (m->shapes)
		// free shapes func
	// ill do these once we merge the parsing tree cuz theres some more things to do :)
	(void)m;
	exit(0);
}

void	adjust_yaw(t_minirt *m, int i)
{
	float old_x;
	float old_z;

	if(i == 0)
	{
		old_x = m->to->x - m->from->x;
		old_z = m->to->z - m->from->z;

		m->to->x = old_x * cos(0.25) - old_z * sin(0.25) + m->from->x;
		m->to->z = old_x * sin(0.25) + old_z * cos(0.25) + m->from->z;
	}
	if(i == 1)
	{
		old_x = m->to->x - m->from->x;
		old_z = m->to->z - m->from->z;
	
		m->to->x = old_x * cos(-0.25) - old_z * sin(-0.25) + m->from->x;
		m->to->z = old_x * sin(-0.25) + old_z * cos(-0.25) + m->from->z;
	}
}

//void	adjust_pitch(t_minirt *m, int i)
//{
//	float	old_y;

//	if (i == UP)
		
//}

// i should make one for up down too (pitch) but im too tireddd :(

int get_key_pressed(int keycode, t_hook_params *hooks)
{
	// I FUCKING COOKED HOLY SHIT IM SO CRAAACKKEEDDDD
	t_minirt *m = hooks->m; 
	if (keycode == W) 
	{
		m->from->z += 0.5;
		m->to->z += 0.5;
		printf("W\n");
	}
	if (keycode == S)
	{
		m->from->z -= 0.5;
		m->to->z -= 0.5;
		printf("S\n");
	}
	if (keycode == A)
	{
		m->from->x -= 0.5;
		m->to->x -= 0.5;
		printf("A\n");
	}
	if (keycode == D)
	{
		m->from->x += 0.5;
		m->to->x += 0.5;
		printf("D\n");
	}
	// found out rotations bymistake lmaoô
	if (keycode == LEFT)
	{
		adjust_yaw(m, 0);
		printf("LEFT\n");
	}
	if (keycode == RIGHT)
	{
		adjust_yaw(m, 1);
		printf("RIGHT\n");
	}
	if (keycode == R)
	{
		m->from = return_tuple_pointer(hooks->original_from.x, hooks->original_from.y, hooks->original_from.z, hooks->original_from.w);
		m->to = return_tuple_pointer(hooks->original_to.x, hooks->original_to.y, hooks->original_to.z, hooks->original_to.w);
		m->up = return_tuple_pointer(hooks->original_up.x, hooks->original_up.y, hooks->original_up.z, hooks->original_up.w);
	}
	//if (keycode == UP)
	//{
	//	adjust_pitch()
	//}
	if (keycode == ESC)
		closert(hooks->m);
	m->cam->view_matrix = view_transform(m->to, m->from, m->up);
	threaded_render(hooks->mlx, m, hooks->m->cam);
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
	t_minirt		*m;
	t_mlx			mlx;
	t_4dmat			temp;
	t_hook_params	*hooks;

	hooks = ft_calloc(1, sizeof(t_hook_params));
	init_mlx(&mlx);
	m = init_default(&mlx);
	m->cam = return_camera_ptr(WIDTH, HEIGHT, PI / 3, NULL);
	m->from = return_tuple_pointer(1, 0, -5, POINT);
	m->to = return_tuple_pointer(0, 0.5, 0, POINT);
	m->up = return_tuple_pointer(0, 1, 0, VECTOR);
	m->cam->view_matrix = view_transform(m->to, m->from, m->up);
	//render(&mlx, m->cam, m);
	threaded_render(&mlx, m, m->cam);
	(void)temp;
	hooks->m = m;
	hooks->mlx = &mlx;
	hooks->original_from = return_point(m->from->x, m->from->y, m->from->z);
	hooks->original_to = return_point(m->to->x, m->to->y, m->to->z);
	hooks->original_up = return_vector(m->up->x, m->up->y, m->up->z);
	
	// I FUCKING COOKED HERE BRO WATCH THIS SHIT RIGHT HERE
	mlx_hook(mlx.win, 2, 1L << 0, get_key_pressed, hooks);
	mlx_hook(mlx.win, 17, 1L << 2, closert, m);
	mlx_loop(&mlx.mlx);
}
